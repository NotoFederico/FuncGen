#pragma once
#include "main.h"
#include "menu.h"
#include "waveforms.h"

void timer2_init(void);
void dutycycle_menu(struct flags *flag);
void print_dutyvalues(struct flags *flag);
void print_magnitude(double *time, int line);
void print_hltimes(struct wave_param *param, struct flags *flag);
void print_freqvalue(struct wave_param *param);
void reverse(char *str,int len);
int  int_to_str(int x, char str[], int d);
void my_ftoa(float n, char *res, int afterpoint);
