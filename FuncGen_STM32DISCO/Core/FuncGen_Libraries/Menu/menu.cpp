#include "menu.h"
#include "push_buttons.h"
#include "main_screen.h"
#include "waveforms.h"
#include "arb.h"
#include "frequency.h"
#include "dutycycle.h"

struct options option = { 1, 1 };
struct flags flag = { 1, 0 };
struct symbol sym = { { 126, '\0' }, { 25, '\0' }, { 179, '\0' } };

extern ADC_HandleTypeDef hadc3;
extern int arbwave_screen, duty_screen, pressed_button, waveform_selected;
extern DAC_HandleTypeDef hdac;

uint16_t* menu(uint16_t *dac_samples_buffer1)
{
    /* Si se presiono algun boton, se determina la nueva pantalla a mostrar*/
    if ((option.current = selector(&option)) != option.old)
    {
        cls_lcd();
        option.old = option.current;
        HAL_ADC_Stop_DMA(&hadc3);
        flag.recoverview = 1;
    }
    /* Muestro la pantalla elegida*/
    switch (option.current)
    {
    case MAIN:
        main_screen(&flag);
        break;
    case WAVEFORMS:
        dac_samples_buffer1 =  waveforms_menu(dac_samples_buffer1, &option, &flag);
        break;
    case FREQUENCY:
        dac_samples_buffer1 = frequency_menu(dac_samples_buffer1, &option, &flag);
        break;
    case DUTY_CYCLE:
        dutycycle_menu(&flag);
        break;
    case ARB_WAVE:
    	arbwave_screen = 1;
        dac_samples_buffer1 = arbwave_menu(dac_samples_buffer1);
        break;
    default:
        print_shifted((char*)"Error, please reset",1,0);
        break;
    }
    return dac_samples_buffer1;
}

int selector(struct options*option)
{
    if (pressed_button == 1)
    {
        pressed_button = 0;
        switch (option->current)
        {
        case MAIN:
            if (button_up == UP)
            {
                if (waveform_selected == ARBITRARY)
                {
                    option->current = ARB_WAVE;
                }
                else
                {
                    if (waveform_selected == RECTANGULAR)
                    {
                        option->current = DUTY_CYCLE;
                    }
                    else
                    {
                        TIM8->CNT = 0;
                        option->current = FREQUENCY;
                    }
                }
            }
            else if (button_down == DOWN)
            {
                option->current = WAVEFORMS;
                TIM8->CNT = 0;
            }
            break;
        case WAVEFORMS:
            if (button_up == UP)
            {
                option->current = MAIN;
            }
            else if (button_down == DOWN)
            {
                if(waveform_selected == ARBITRARY)
                {
                    option->current = ARB_WAVE;
                }
                else
                {
                    option->current = FREQUENCY;
                }
                TIM8->CNT = 0;
            }
            break;
        case FREQUENCY:
            if (button_up == UP)
            {
                option->current = WAVEFORMS;
            }
            else if (button_down == DOWN)
            {
                if (waveform_selected == ARBITRARY)
                {
                    option->current = ARB_WAVE;
                }
                else
                {
                    if (waveform_selected == RECTANGULAR)
                    {
                        option->current = DUTY_CYCLE;
                    }
                    else
                    {
                        option->current = MAIN;
                    }
                }
            }
            break;
        case DUTY_CYCLE:
            if (button_up == UP)
            {
                option->current = FREQUENCY;
            }
            else if (button_down == DOWN)
            {
                option->current = MAIN;
            }
            break;
        case ARB_WAVE:
            if (button_up == UP)
            {
                option->current = WAVEFORMS;
            }
            else if (button_down == DOWN)
            {
                option->current = MAIN;
            }
            break;
        }
        flag_callback_menu = 0;
        button_up = NONE;
        button_down = NONE;
    }
    return option->current;
}

void print_arrowup(int row, int pos)
{
    int i;
    for (i = 0; i < 20; i++)
    {
        print_shifted(sym.empty_space, row, i);
    }
    print_shifted(sym.arrow_up, row, pos);
}

void print_arrowright(int line, int pos)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        print_shifted(sym.empty_space, i, pos);
    }
    print_shifted(sym.arrow_right, line, pos);
}

