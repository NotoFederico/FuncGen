#include "common_waves.h"
#include <stdlib.h>
#include <stdio.h>

#define ARR_MAX 65535
#define SAMPLES_MAX 2000
#define SAMPLES_MIN 100
#define SAMPLERATE_MAX 10500000

extern DAC_HandleTypeDef hdac;
extern struct wave_param param;

const double offset = 5;
const double timer_fclock = 84000000;

// idea de utilizar un pin para medir la frecuencia y corregirla

void Load_Square(struct wave_param *param)
{
    uint32_t ARRValue = (uint32_t) (SystemCoreClock / (param->frequency * 2) - 1); //ver si con un valor dummy alcanza
    TIM2->ARR = ARRValue;
    TIM2->CCR1 = ARRValue / 2;
}

void Load_Rectangular(struct wave_param *param)
{
    uint32_t ARRValue = (uint32_t) (SystemCoreClock / (param->frequency * 2) - 1); //ver si con un valor dummy alcanza
    TIM2->ARR = ARRValue;
    TIM2->CCR1 = (float) (ARRValue * (float) (param->duty_cycle / 100));
}

void Load_Step(int state)
{
    uint32_t ARRValue = 100;
    TIM2->ARR = ARRValue;
    if (state == 0)
    {
        TIM2->CCR1 = 0;
    }
    else if (state == 1)
    {
        TIM2->CCR1 = ARRValue;
    }
}

uint16_t* Load_Sine(uint16_t *dac_samples_buffer4, struct wave_param *param) //usar nombres diferentes
{
    volatile float32_t step = 0;
    volatile uint16_t i = 0;
    param->offset = 2047;
    TIM6->ARR = param->arr;
    if (dac_samples_buffer4 != NULL)
    {
        free(dac_samples_buffer4);
        HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
    }
    dac_samples_buffer4 = (uint16_t*) malloc(param->sample_size * sizeof(uint16_t));
    for (i = 0; i <= param->sample_size; i++)
    {
        dac_samples_buffer4[i] = (uint16_t) (arm_sin_f32(step * (M_PI / 180)) * (param->amplitude / 2) + param->offset);
        step = step + 360.0f / (float) param->sample_size;
    }
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*) (dac_samples_buffer4), (uint32_t) param->sample_size, DAC_ALIGN_12B_R);
    return dac_samples_buffer4;
}

uint16_t* Load_Hav(uint16_t *dac_samples_buffer, struct wave_param *param)
{
    volatile float32_t step = 0;
    volatile uint16_t i;
    param->offset = 2047;
    TIM6->ARR = param->arr;
    if (dac_samples_buffer != NULL)
    {
        free(dac_samples_buffer);
    }
    dac_samples_buffer = (uint16_t*) malloc(param->sample_size * sizeof(uint16_t));
    for (i = 0; i < param->sample_size; i++)
    {
        dac_samples_buffer[i] = (uint16_t) (((1 - arm_cos_f32(step * (M_PI / 180))) / 2) * (param->amplitude / 2) + param->offset);
        step = step + 360.0f / (float) param->sample_size;
    }
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*) dac_samples_buffer, param->sample_size, DAC_ALIGN_12B_R);
    return dac_samples_buffer;
}

uint16_t* Load_Triangular(uint16_t *dac_samples_buffer, struct wave_param *param)
{
    volatile uint16_t i = 0;
    TIM6->ARR = param->arr;
    if (dac_samples_buffer != NULL)
    {
        free(dac_samples_buffer);
    }
    dac_samples_buffer = (uint16_t*) malloc(param->sample_size * sizeof(uint16_t));
    while (i <= param->sample_size)
    {
        if (i < param->sample_size / 2)
        {
            dac_samples_buffer[i] = (int) ((param->amplitude * i * 2) / param->sample_size);
        }
        else
        {
            dac_samples_buffer[i] = (int) (param->amplitude * 2 - (param->amplitude * i * 2) / param->sample_size);
        }
        i++;
    }
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*) dac_samples_buffer, param->sample_size, DAC_ALIGN_12B_R);
    return dac_samples_buffer;
}

uint16_t* Load_Sawtooth(uint16_t *dac_samples_buffer, struct wave_param *param)
{
    volatile uint16_t i = 0;
    TIM6->ARR = param->arr;
    if (dac_samples_buffer != NULL)
    {
        free(dac_samples_buffer);
    }
    dac_samples_buffer = (uint16_t*) malloc(param->sample_size * sizeof(uint16_t));

    while (i <= param->sample_size)
    {
        if (i < param->sample_size)
        {
            dac_samples_buffer[i] = ((param->amplitude * i) / param->sample_size);
        }
        i++;
    }
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*) dac_samples_buffer, param->sample_size, DAC_ALIGN_12B_R);
    return dac_samples_buffer;
}

uint16_t* Load_White(uint16_t *dac_samples_buffer, struct wave_param *param)
{
    volatile uint16_t i = 0;
    TIM6->ARR = param->arr;
    if (dac_samples_buffer != NULL)
    {
        free(dac_samples_buffer);
    }
    dac_samples_buffer = (uint16_t*) malloc(param->sample_size * sizeof(uint16_t));
    for (i = 0; i < param->sample_size; i++)
    {
        dac_samples_buffer[i] =  rand() % param->amplitude;
    }
    HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*) dac_samples_buffer, param->sample_size, DAC_ALIGN_12B_R);
    return dac_samples_buffer;
}

void SampleRate_Algorithm(struct wave_param *param)
{
    HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
    double arr, samples, f_calc, cond1, best = 100;
    for (samples = SAMPLES_MAX; samples >= SAMPLES_MIN; samples--)
    {
        arr = trunc((timer_fclock / param->frequency) * (1 / samples) - 1);
        f_calc = ((timer_fclock) / (samples * (arr + 1)));
        cond1 = ((timer_fclock) / ((arr + 1)));
        if ((cond1 <= 0.8 * SAMPLERATE_MAX) && arr <= ARR_MAX && (f_calc >= (param->frequency - offset)) && (f_calc <= (param->frequency + offset)))
        {
            if (fabs(param->frequency - f_calc) < best)
            {
                best = f_calc - param->frequency;
                param->arr = arr;
                param->sample_size = samples;
            }
        }
    }
}

