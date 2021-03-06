#include "main_screen.h"
#include "waveforms.h"
#include "dutycycle.h"
#include "frequency.h"

const double timer_fclock = 84000000;

extern int arbwave_loaded;
extern int waveform_selected;
extern int waveform_loaded;
extern uint32_t arbwave_size;
extern int counter;
extern ADC_HandleTypeDef hadc3;
uint16_t adc_samples_buffer[3];


void main_screen(struct flags *flag)
{
	/*Si se cambia de pantalla y se vuelve a ésta se ejecuta este bloque*/
    if(flag->recoverview == 1)
    {
        flag->recoverview = 0;
        print_labels();
        print_params();
        HAL_ADC_Start_DMA(&hadc3, (uint32_t *) adc_samples_buffer, sizeof(adc_samples_buffer));
        counter = 0;
    }
    if(counter >= 400) //actualizo cada 400 ms, sino la tasa de refresco es muy alta
    {
        print_offset();
        print_amplitude();
        counter = 0;
    }
}

/* Imprimo en el display las etiquetas de esta pantalla*/
void print_labels(void)
{
    print_shifted((char*)"WAVE:", 1, 0);
    print_shifted((char*)"FREQ:", 2, 0);
    print_shifted((char*)"Hz", 2, 12);
    print_shifted((char*)"AMP:", 3, 0);
    print_shifted((char*)"Vp", 3, 13);
    print_shifted((char*)"OFST:", 4, 0);
    print_shifted((char*)"V", 4, 13);
    print_shifted((char*)"DUT:", 3, 16);
}
/* Imprimo en el display los parametros de la forma de onda segun corresponda*/
void print_params(void)
{
    char buffer[10];
    if (waveform_selected != ARBITRARY)
    {
        snprintf(buffer,sizeof(buffer), "%d", param.frequency);
        arbwave_loaded = 0;
    }
    else
    {
        if (waveform_selected == ARBITRARY && arbwave_loaded == 1)
        {
            int arb_f = (int) (timer_fclock / ((TIM6->ARR + 1) * arbwave_size));
            snprintf(buffer, sizeof(buffer), "%d", arb_f);
        }
        else
        {
            snprintf(buffer, sizeof(buffer), "N/A");
        }
    }
    print_shifted(buffer, 2, 7);
    if(waveform_selected == RECTANGULAR || waveform_selected == SQUARE)
    {
        if(waveform_selected == SQUARE)
        {
            snprintf(buffer, sizeof(buffer), "%d", 50);
        }
        else
        {
            snprintf(buffer, sizeof(buffer), "%d", (int) param.duty_cycle);
        }
        print_shifted((char*)"%", 4, 19);
    }
    else
    {
        snprintf(buffer, sizeof(buffer), "N/A ");
    }
    print_shifted(buffer, 4, 16);
    get_waveform_name();
}

/* Obtengo el nombre de la forma de onda generada*/
void get_waveform_name(void)
{
    char *waveforms_array[8] = { (char*)"SINE     ", (char*)"HAVSINE ", (char*)"SQUARE   ", (char*)"RECTANGULAR", (char*)"TRIANGULAR", (char*)"SAWTOOTH", (char*)"W.NOISE   ", (char*)"ARBITRARY  " };
    if ( waveform_selected > 8 ||  waveform_selected < 0 ||  waveform_loaded == -1)
    {
        print_shifted((char*)"NONE", 1, 7);
    }
    else
    {
        print_shifted( waveforms_array[ waveform_selected], 1, 7);
    }
}
/*Calculo e imprimo la amplitud de la forma de onda generada*/
void print_amplitude(void)
{
    volatile double amp;
    char  aux_buffer[8] = "\0";
    //uint16_t adc_samples_buffer1[3] = {'\0'};
    //HAL_ADC_Start_DMA(&hadc3, (uint32_t *) &adc_samples_buffer2, 3);
    amp = (double) adc_getsampleavg_n_delete_x(hadc3, 0, 512, 128);
    amp = ((amp*20.20))/4095/2;
    if(waveform_selected == HAV)
    {
    	amp = amp/2;
    }
    snprintf(aux_buffer, sizeof(aux_buffer),"%.2f ",amp);
    //my_ftoa(amp/2, buf, 3);
    print_shifted(aux_buffer, 3, 7);
}

/*Calculo e imprimo el offset de la forma de onda generada*/
void print_offset()
{
    double offset;
    double sign;
    char   aux_buffer[8] = "\0";
    offset = (double) adc_getsampleavg_n_delete_x(hadc3, 1, 512, 128);
    offset = abs((offset*5.2)/4095);
    snprintf(aux_buffer, sizeof(aux_buffer),"%.3f",offset);
    //my_ftoa(offset, buf, 3);
    print_shifted(aux_buffer, 4, 7);
    sign = (double) adc_getsampleavg_n_delete_x(hadc3, 2, 512, 128);
    if(sign>=2150) //existe un desfasaje de unas pocas cuentas entre el 0V y el cambio de signo (por eso 2150 y no 2047)
        print_shifted((char*)"-",4,6);
    else
        print_shifted((char*)"+",4,6);
}

/**
 * @brief Get the average of N-X ADC samples
 * @param Numbre of ADC samples to be averaged
 * @param Numbre of ADC samples to be averaged
 * @retval The average value
 */
uint16_t adc_getsampleavg_n_delete_x(ADC_HandleTypeDef hadc, int pos, uint16_t N, uint16_t X)
{
    uint32_t avg_sample =0x00;
    uint16_t *adc_sample;
    uint16_t index=0x00;
    adc_sample = (uint16_t*) malloc(N*sizeof(uint16_t));
    for (index=0x00; index<N; index++)
    {
        /* ADC start conv */
//adc_sample[index] = HAL_ADC_GetValue(&hadc);
        adc_sample[index] = adc_samples_buffer[pos];
        /* Wait end of conversion */
//while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
        /* Store ADC samples */
    }
    /* Sort the N-X ADC samples */
    sort_tab(adc_sample,N);
    /* Add the N ADC samples */
    for (index=X/2; index<N-X/2; index++)
    {
        avg_sample += adc_sample[index];
    }
    /* Compute the average of N-X ADC sample */
    avg_sample /= N-X;
    if (adc_sample != NULL)
    {
        free(adc_sample);
    }
    /* Return average value */
    return avg_sample;
}
/**
Averaging of N-X ADC samples: source code AN4073
28/32 DocID022945 Rev 5
 * @brief Sort the N ADC samples
 * @param ADC samples to be sorted
 * @param Numbre of ADC samples to be sorted
 * @retval None
 */
void sort_tab(uint16_t tab[], uint16_t lenght)
{
    uint16_t l=0x00, exchange =0x01;
    uint16_t tmp=0x00;
    /* Sort tab */
    while(exchange==1)
    {
        exchange=0;
        for(l=0; l<lenght-1; l++)
        {
            if( tab[l] > tab[l+1] )
            {
                tmp = tab[l];
                tab[l] = tab[l+1];
                tab[l+1] = tmp;
                exchange=1;
            }
        }
    }
}
