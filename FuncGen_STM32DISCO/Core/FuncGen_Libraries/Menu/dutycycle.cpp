#include <magnitude.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "dutycycle.h"
#include "main.h"

using namespace std;

extern int counter;

magnitude *duty = new magnitude(50, 99); //default value, despues valor limite

void dutycycle_menu(struct flags *flag)
{
    TIM1->ARR = 39; // Selecci�n de numeros - 10 opciones de a pasos de a 4 (0 a 9)
    TIM8->ARR = 7; // Antes 7, Seleccion de unidades - 2 opciones de a pasos de a 4 (0 a 1)
    int aux = param.duty_cycle;
    print_dutyvalues(flag);
    print_freqvalue(&param);
    if(counter >= 300)
    {
    int unity_selected = TIM8->CNT >> 2;
    int digit_selected = TIM1->CNT >> 2;
    if (unity_selected != duty->place_value)
    {
        if(unity_selected!=1 && unity_selected!=0)
        {
            unity_selected = 0;
            TIM8->CNT = 0;
        }
        print_arrowup(2, 13 - unity_selected + 1);
    }
    param.duty_cycle = (float32_t) duty->refresh(param.duty_cycle, unity_selected, digit_selected, 2);
    counter = 0;

    }
    if(param.duty_cycle!=aux)
    {
        static char str1[2];
        static char str2[2];
        sprintf(str1, "%d", duty->magnitude_vector.at(0));
        sprintf(str2, "%d", duty->magnitude_vector.at(1));
        print_shifted(str1, 1, 13);
        print_shifted(str2, 1, 14);
        print_hltimes(&param, flag);
        Load_Rectangular(&param);
    }
}

void print_dutyvalues(struct flags *flag)
{
    if (flag->recoverview == 1)
    {
        static char str1[2];
        static char str2[2];
        print_shifted((char*)"%", 1, 15);
        print_shifted((char*)"DUTY CYCLE  ", 1, 0);
        sprintf(str1, "%d", duty->magnitude_vector.at(0));
        sprintf(str2, "%d", duty->magnitude_vector.at(1));
        print_shifted(str1, 1, 13);
        print_shifted(str2, 1, 14);
        print_arrowup(2, 14);
        TIM1->CNT = duty->magnitude_vector.at((2 - 1) - duty->place_value);
        flag->recoverview = 0;
        print_hltimes(&param, flag);
        Load_Rectangular(&param);
    }
}

void print_magnitude(double *time, int line)
{
    int m;
    if (*time < 0.000001)
    {
        m = 1000000000;
        print_shifted((char*)"ns", line, 12);
    }
    else if (*time < 0.001)
    {
        m = 1000000;
        print_shifted((char*)"us", line, 12);
    }
    else if (*time < 0.1)
    {
        m = 1000;
        print_shifted((char*)"ms", line, 12);
    }
    else
    {
        m = 1;
        print_shifted((char*)"s", line, 12);
    }
    *time = (*time) * m;
}

void print_hltimes(struct wave_param *param, struct flags *flag)
{
    double time_on, time_off;
    char time_buf[10] = "\0";
    print_shifted((char*)"Ton:", 3, 0);
    print_shifted((char*)"Toff:", 4, 0);
    time_on = (1 / ((double) param->frequency))  * ((double) param->duty_cycle * 0.01);
    time_off = 1 / (double) param->frequency - time_on;
    print_magnitude(&time_on, 3);
    snprintf(time_buf,sizeof(time_buf),"%.3f",time_on);
    //my_ftoa(time_on, time_buf, 3);
    //strcat(time_buf,"\0");
    print_shifted(time_buf, 3, 5);
    print_magnitude(&time_off, 4);
    snprintf(time_buf,sizeof(time_buf),"%.3f",time_off);
    //my_ftoa(time_off, time_buf,3);
    //strcat(time_buf,"\0");
    print_shifted(time_buf, 4, 5);
}

void print_freqvalue(struct wave_param *param)
{
    char buffer[10];
    print_shifted((char*)"Hz", 2, 10);
    print_shifted((char*)"FREQ:", 2, 0);
    snprintf(buffer, sizeof(buffer), "%d", param->frequency);
    print_shifted(buffer, 2, 5);
}

// Reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
/*
// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void my_ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int) n;
    // Extract floating part
    float fpart = n - (float) ipart;
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
        intToStr((int) fpart, res + i + 1, afterpoint);
    }
}
*/
void timer2_init(void)
{
    /* USER CODE BEGIN TIM2_Init 0 */
    /* USER CODE END TIM2_Init 0 */
    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    TIM_OC_InitTypeDef sConfigOC = { 0 };
    /* USER CODE BEGIN TIM2_Init 1 */
    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 4200;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig)!= HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)!= HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 2100;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1)!= HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */
    /* USER CODE END TIM2_Init 2 */
    HAL_TIM_MspPostInit(&htim2);
    HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}
