#pragma once
#include "main.h"
#include "menu.h"
#include "common_waves.h"

extern struct wave_param param;

int get_waveformloaded(void);
uint16_t* waveforms_menu(uint16_t *array, struct options *option, struct flags *flag);
void waveforms_circularmenu(void);
void recover_view(struct flags *flag);

