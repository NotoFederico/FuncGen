#include "main.h"
#include "waveforms.h"
#include "frequency.h"
#include "magnitude.h"
#include <algorithm>

extern int counter;
magnitude *freq = new magnitude(10000, 20000); //default value, despues valor limite

uint16_t* frequency_menu(uint16_t *dac_samples_buffer3, struct options *option, struct flags *flag)
{
    int aux = param.frequency;
    TIM1->ARR = 39; // Selecci�n de numeros - 10 opciones de a pasos de a 4 (0 a 9)
    TIM8->ARR = 19; // Seleccion de unidades - 5 opciones de a pasos de a 4 (1 a 5)
    print_freqvalues(flag);
    if(counter >= 300)
    {
    int unity_selected = TIM8->CNT >> 2;
    int digit_selected = TIM1->CNT >> 2;
    if (unity_selected != freq->place_value)
    {
        print_arrowup(4, 15 - unity_selected);
    }

    param.frequency = (float32_t) freq->refresh(param.frequency, unity_selected, digit_selected, 5);
    counter = 0;
    }
    if (param.frequency != aux)
    {

        int n = freq->magnitude_vector.size();
        char *arr;
        arr = (char*) malloc(sizeof(char));
        for (int i = 0; i < n; i++)
        {
            arr[i] = (char) (freq->magnitude_vector[i] + 48);
        }
        print_shifted(arr, 3, 11);
        free(arr);

        flag->reloadwave = 1;
        dac_samples_buffer3 = waveforms_menu(dac_samples_buffer3, option, flag);
        flag->reloadwave = 0;

    }
    else
    {
        flag->reloadwave = 0;
    }
    return dac_samples_buffer3;
}

void print_freqvalues(struct flags *flag)
{
    if (flag->recoverview == 1)
    {
        print_shifted((char*)"FREQUENCY  ",1,0);
        print_shifted((char*)"Hz", 3, 17);
        print_shifted((char*)" ", 3, 16);
        print_shifted((char*)"Value:", 3, 1);

        int n = freq->magnitude_vector.size();
        char *arr;
        arr = (char*) malloc(sizeof(char));
        for (int i = 0; i < n; i++)
        {
            arr[i] = (char) (freq->magnitude_vector[i] + 48);
        }
        print_shifted(arr, 3, 11);
        free(arr);

        print_arrowup(4, 15 - freq->place_value);
        TIM1->CNT = freq->magnitude_vector.at(( 5 - 1) - freq->place_value) << 2;
        flag->recoverview = 0;
        counter = 0;
    }
}
