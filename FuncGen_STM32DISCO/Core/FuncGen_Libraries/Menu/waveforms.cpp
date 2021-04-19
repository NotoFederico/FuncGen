#include "waveforms.h"
#include "dutycycle.h"
extern DAC_HandleTypeDef hdac;
extern int arbwave_loaded;
extern int counter;

char *waveforms_array[8] = { (char*)"SINE    ", (char*)"HAVSINE ", (char*)"SQUARE  ", (char*)"RECT.   ", (char*)"TRIANG. ", (char*)"SAWTOOTH", (char*)"W.NOISE ", (char*)"ARB.WAVE"};
int initial_waveform = 0, initial_waveform_old = -1, row_selected = 1, row_selected_old = -1;
int waveform_selected = 0, waveform_loaded = -1, shift_flag = 0;
int arbwave_screen = 0, duty_screen = 0;


uint16_t* waveforms_menu(uint16_t *dac_samples_buffer2, struct options *option, struct flags *flag)
{
	/*Determino la forma de onda a generar segun sea seleccionada en un menu circular mostrado en el display*/
    if (option->current == WAVEFORMS) {
        recover_view(flag);
        waveforms_circularmenu(); // Obtiene el valor de la forma de onda que corresponde de acuerdo a la posicion del encoder
    }
    if(waveform_selected!=ARBITRARY)
    	arbwave_loaded = 0;
    /*Genero la forma de onda*/
    switch (waveform_selected) {
    case SQUARE:
        if (waveform_selected != waveform_loaded || flag->reloadwave == 1) {
            if (flag->reloadwave == 1) {
            	timer2_init();
            }
            waveform_loaded = SQUARE;
            Load_Square(&param);
            flag->reloadwave = 0;
        	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_RESET);
        }
        break;
    case RECTANGULAR:
        if (waveform_selected != waveform_loaded || flag->reloadwave == 1) {
            duty_screen = 1;
            if (flag->reloadwave == 1) {
                timer2_init();
            }
            Load_Rectangular(&param);
            waveform_loaded = RECTANGULAR;
            flag->reloadwave = 0;
        	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_RESET);
        }
        break;
    case SINE:
        if (waveform_selected != waveform_loaded || flag->reloadwave == 1) {
            waveform_loaded = SINE;
            SampleRate_Algorithm(&param);
            dac_samples_buffer2 = Load_Sine(dac_samples_buffer2, &param);
            flag->reloadwave = 0;
        	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_SET);
        }
        break;
    case HAV:
        if (waveform_selected != waveform_loaded || flag->reloadwave == 1) {
            waveform_loaded = HAV;
            SampleRate_Algorithm(&param);
            dac_samples_buffer2 = Load_Hav(dac_samples_buffer2, &param);
            flag->reloadwave = 0;
        	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_SET);

        }
        break;
    case TRIANGULAR:
        if (waveform_selected != waveform_loaded || flag->reloadwave == 1) {
            waveform_loaded = TRIANGULAR;
            SampleRate_Algorithm(&param);
            dac_samples_buffer2 = Load_Triangular(dac_samples_buffer2, &param);
            flag->reloadwave = 0;
        	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_SET);
        }
        break;
    case SAWTOOTH:
        if (waveform_selected != waveform_loaded || flag->reloadwave == 1) {
            waveform_loaded = SAWTOOTH;
            SampleRate_Algorithm(&param);
            dac_samples_buffer2 = Load_Sawtooth(dac_samples_buffer2, &param);
            flag->reloadwave = 0;
        	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_SET);
        }
        break;
    case WHITE:
        if (waveform_selected != waveform_loaded || flag->reloadwave == 1) {
            waveform_loaded = WHITE;
            SampleRate_Algorithm(&param);
            dac_samples_buffer2 = Load_White(dac_samples_buffer2, &param);
            flag->reloadwave = 0;
        	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_SET);
        }
        break;
    case ARBITRARY:
        waveform_loaded = ARBITRARY;
        if(arbwave_loaded == 0)
        {
		HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
        }
        arbwave_screen = 1;
    	HAL_GPIO_WritePin(CD4051_A_GPIO_Port, CD4051_A_Pin, GPIO_PIN_SET);
        break;
    }
    if (waveform_selected != RECTANGULAR) {
        duty_screen = 0;
    }
    if (waveform_selected != ARBITRARY) {
        arbwave_screen = 0;
    }
    return dac_samples_buffer2;
}

/*Actualizo el menu circular si se gira el encoder*/
void waveforms_circularmenu(void)
{
    volatile int i = 0;
    volatile int aux = 0;
    TIM1->ARR = 15; // la flecha tiene 4 lineas para recorrer (4*4-1)

if(counter >= 300)
{
    uint32_t tim_cnt = TIM1->CNT;
    row_selected = (tim_cnt >> 2) + 1;

    if(row_selected!=row_selected_old)
    {
//Bloque 1
    if (row_selected == 4 && row_selected_old == 1) {
        TIM1->CNT = (row_selected_old << 2) - 1;
        shift_flag = -1;
        if (--waveform_selected < SINE) {
            waveform_selected = ARBITRARY;
        }
    } else if (row_selected == 1 && row_selected_old == 4) {
        TIM1->CNT = (row_selected_old << 2) - 1;
        shift_flag = 1;
        if (++waveform_selected > ARBITRARY) {
            waveform_selected = SINE;
        }
    }
// Fin de Bloque 1
// Bloque 2
    if (shift_flag != 0) {
    	initial_waveform += shift_flag;
        shift_flag = 0;
        if (initial_waveform > ARBITRARY) {
            initial_waveform = SINE;
        }
        if (initial_waveform < SINE) {initial_waveform = ARBITRARY;
        }
        row_selected = row_selected_old;
    }
// Fin de Bloque 2
//Bloque 3
    if (initial_waveform != initial_waveform_old) {
        int aux = 0;
        for (i = 1; i <= 4; i++) {
            if (initial_waveform == TRIANGULAR || initial_waveform == SAWTOOTH || initial_waveform == WHITE || initial_waveform == ARBITRARY) {
                if ((initial_waveform + i - 1) == 8 || (initial_waveform + i - 1) == 9 || (initial_waveform + i - 1)  == 10) {
                    aux = -8;
                } else {
                    aux = 0;
                }
            }
            print_shifted(waveforms_array[initial_waveform + i - 1 + aux], i, 12);
        }
        initial_waveform_old = initial_waveform;
    }
//Fin de Bloque 3
//Bloque 4
    if (row_selected != row_selected_old) {
        row_selected_old = row_selected;
        print_arrowright(row_selected, 11);
    }
//Fin de Bloque 4
//Bloque 5
    if (initial_waveform == TRIANGULAR || initial_waveform == SAWTOOTH || initial_waveform == WHITE || initial_waveform == ARBITRARY) {
        if ((initial_waveform +row_selected - 1) == 8 || (initial_waveform + row_selected - 1) == 9 || (initial_waveform + row_selected - 1) == 10) {
            aux = -8;
        } else {
            aux = 0;
        }
    }
//Fin de bloque 5
    waveform_selected = initial_waveform + row_selected - 1 + aux;
    aux = 0;
    }
    counter = 0;

	}
}

/*Si se cambia de pantalla y se vuelve a ésta, se ejecuta éste bloque de código*/
/*Redibujo el menu circular segun el estado previo a cambiar de pantalla*/
void recover_view(struct flags *flag)
{

    if (flag->recoverview == 1)
    {
        int i;
        int aux = 0;
        TIM1->ARR = 15;
        flag->recoverview = 0;
        flag->reloadwave = 1;
        print_shifted((char*)"WAVEFORMS", 1, 0);
        for (i = 1; i <= 4; i++) {
            if (initial_waveform == TRIANGULAR || initial_waveform == SAWTOOTH || initial_waveform == WHITE || initial_waveform == ARBITRARY) {
                if ((initial_waveform + i - 1) == 8 || (initial_waveform + i - 1)  == 9 || (initial_waveform + i - 1) == 10) {
                    aux = -8;
                } else {
                    aux = 0;
                }
            }
            print_shifted(waveforms_array[initial_waveform + i - 1 + aux], i, 12);
        }
        print_arrowright(row_selected, 11);
        TIM1->CNT = (row_selected <<2) - 1;
        counter = 0;
    }
}

/*Devuelvo el valor (#define) de la forma de onda generada */
int get_waveformloaded(void)
{
    int cw = waveform_selected;
    return cw;
}
