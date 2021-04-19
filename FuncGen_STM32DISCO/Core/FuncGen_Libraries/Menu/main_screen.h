#include "main.h"
#include "menu.h"

uint16_t adc_getsampleavg_n_delete_x(ADC_HandleTypeDef hadc, int pos, uint16_t N, uint16_t X);
void sort_tab(uint16_t tab[], uint16_t lenght);
void main_screen(struct flags *flag);
void print_labels(void);
void print_params(void);
void print_amplitude(void);
void print_offset(void);
void get_waveform_name(void);
