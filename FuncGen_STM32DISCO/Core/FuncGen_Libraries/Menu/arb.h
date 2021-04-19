#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "menu.h"

uint16_t* arbwave_menu(uint16_t *dac_samples_buffer3);
void params_parser(char* arr, uint32_t* data_size, uint32_t* samplerate_size);
static void Flush_Buffer(uint8_t* pBuffer, uint16_t BufferLength);
void load_percentage(uint16_t p, uint16_t a);

