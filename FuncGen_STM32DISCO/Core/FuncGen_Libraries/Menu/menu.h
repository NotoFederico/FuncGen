#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "lcd.h"
//#include "push_buttons.h"

#define E_SW1_ON   1
#define E_SW1_OFF  0
#define E_SW2_ON   1
#define E_SW2_OFF  0

#define MAIN	   1
#define WAVEFORMS  2
#define FREQUENCY  3
#define DUTY_CYCLE 4
#define ARB_WAVE   5


#define SINE				0
#define HAV					1
#define SQUARE   			2
#define RECTANGULAR			3
#define TRIANGULAR			4
#define	SAWTOOTH			5
#define WHITE				6
#define ARBITRARY   		7


extern TIM_HandleTypeDef htim2;
extern int8_t flag_callback_menu;
extern int button_up, button_down;
extern volatile uint16_t button_callback;

struct symbol
{
    char arrow_right[2];
    char empty_space[2];
    char arrow_up[2];
};

struct options
{
    int current;
    int old;
};

struct flags
{
    int recoverview;
    int reloadwave;
};

uint16_t* menu(uint16_t *dac_samples_buffer);
int selector(struct options *option);
void print_arrowup(int row, int pos);
void print_arrowright(int row, int pos);
