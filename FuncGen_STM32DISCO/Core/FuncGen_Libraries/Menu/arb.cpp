#include "main.h"
#include "arb.h"
#include "string.h"

#define BUFFER_SIZE 20

extern I2C_HandleTypeDef hi2c1;
extern DAC_HandleTypeDef hdac;
extern struct options option;
extern int8_t flag_callback_menu;

uint32_t arbwave_size = 0;
uint32_t arbwave_sample_rate = 0;
uint16_t arb_paramsize = 0;
uint16_t pos = 0;
uint8_t *buffer;
uint8_t RxNumData[2] = {'\0'};
char pos_bf[10] = {'\0'};
int state_machine = 0;
int sm_flag = 1;
int arbwave_loaded = 0;
const double timer_fclock = 84000000;

uint16_t* arbwave_menu(uint16_t *dac_samples_buffer3)
{
    switch(state_machine)
    {
    case 0: //recibo el tamaño de caracteres de los parametros de la onda arbitraria
        if(sm_flag == 1)
        {
            state_machine = 1;
            sm_flag = 0;
            HAL_I2C_Slave_Receive_IT(&hi2c1, RxNumData, (uint16_t) 1);
        }
        break;
    case 1: //recibo los datos de parametro de la forma de onda
        print_shifted((char*)"Choose an Arb. Wave", 1, 0);
        print_shifted((char*)"http://esp8266/local", 2, 0);
        if(sm_flag == 1)
        {
            if(arb_paramsize == 0)
            {
                print_shifted((char*)"PARAMS SIZE ERROR", 3, 0);
            }
            else
            {
                state_machine = 2;
                sm_flag = 0;
                print_shifted((char*)"Getting ready...    ", 3, 0);
                if(buffer!=NULL)
                {
                    free(buffer);
                }
                buffer = (uint8_t*) malloc(sizeof(uint8_t)*20);
                Flush_Buffer((uint8_t*) buffer, BUFFER_SIZE);
                HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
                HAL_I2C_Slave_Receive_IT(&hi2c1, buffer, arb_paramsize);
            }
        }
        break;
    case 2:
        if(sm_flag == 1)
        {
            state_machine = 3;
            sm_flag = 0;
            print_shifted((char*)"Please wait...  ", 3, 0);
            print_shifted((char*)"Status: 0%  ", 4, 0);
            params_parser((char*)buffer, &arbwave_size, &arbwave_sample_rate);
            Flush_Buffer((uint8_t*) buffer, BUFFER_SIZE);
            if(dac_samples_buffer3!=NULL)
            {
                free(dac_samples_buffer3);
            }
            dac_samples_buffer3 = (uint16_t*) malloc(sizeof(uint16_t)*arbwave_size);
            HAL_I2C_Slave_Receive_IT(&hi2c1, buffer, (uint16_t) 4);
        }
        break;
    case 3:
        if(sm_flag == 1)
        {
            sm_flag = 0;
            load_percentage(pos, arbwave_size);
            dac_samples_buffer3[pos++] = (uint16_t) atoi((char*)buffer);
            Flush_Buffer((uint8_t*) buffer, BUFFER_SIZE);
            if(pos<arbwave_size)
            {
                HAL_I2C_Slave_Receive_IT(&hi2c1, buffer,  (uint16_t) 4);
            }
            else
            {
                state_machine = 4;
            }
        }
        break;
    case 4:
        HAL_I2C_AbortCpltCallback(&hi2c1);
        print_shifted((char*)"Success            ", 3, 0);
        TIM6->ARR = (uint32_t) ( timer_fclock /  arbwave_sample_rate - 1);
        HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*) dac_samples_buffer3, arbwave_size, DAC_ALIGN_12B_R);
        arbwave_loaded = 1;
        state_machine = 0;
        sm_flag = 1;
        pos = 0;
        break;
    }
    return dac_samples_buffer3;
}

/**
  * @brief  Flushes the buffer
  * @param  pBuffer: buffers to be flushed.
  * @param  BufferLength: buffer's length
  * @retval None
  */

void load_percentage(uint16_t p, uint16_t a)
{
    int r = (100*p)/a + 1;
    if(r == 25)
        print_shifted((char*)"25%", 4, 8);
    else if(r == 50)
        print_shifted((char*)"50%", 4, 8);
    else if(r == 75 )
        print_shifted((char*)"75%", 4, 8);
    else if(r == 100 )
        print_shifted((char*)"100%", 4, 8);
}

static void Flush_Buffer(uint8_t* pBuffer, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        *pBuffer = 0;
        pBuffer++;
    }
}


void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    sm_flag = 1;
    if(state_machine == 1)
    {
        arb_paramsize = RxNumData[0];
        //print_shifted("Check 1",2,1);
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    uint32_t error = 0;
    char buffer1[10] = {'\0'};
    error = HAL_I2C_GetError(&hi2c1);
    sprintf(buffer1,"%d", (int) error );
    print_shifted((char*)"Error:", 4, 11);
    print_shifted(buffer1,4,6);
}

void params_parser(char* arr, uint32_t* data_size, uint32_t* samplerate_size)
{
    char aux_buffer[10] = {'\0'};
    char *ptr1;
    char *ptr2;
    ptr1 = strchr(arr,',');
    ptr2 = arr;
    for(int i = 0; ptr1!=ptr2; i++)
    {
        aux_buffer[i] = *(ptr2++);
    }
    *data_size = atoi(aux_buffer);
    ptr1 = strchr(arr,'\0');
    if(*ptr2 == ',')
        ptr2++;
    for(int i=0; i<10; i++)
        aux_buffer[i] = '\0';
    for(int i = 0; ptr1!=ptr2; i++)
    {
        aux_buffer[i] = *(ptr2++);
    }
    *samplerate_size = atoi(aux_buffer);
}
