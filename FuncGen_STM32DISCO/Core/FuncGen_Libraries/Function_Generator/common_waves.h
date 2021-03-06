#include "main.h"
#include "arm_math.h"
#include "arm_common_tables.h"
//#define M_PI 3.14159265358979323846f

struct wave_param
{
    uint16_t frequency;
    uint16_t amplitude;
    uint16_t offset;
    float32_t duty_cycle;
    double arr;
    double sample_size;
};

int Size_Of_Buffer(struct wave_param *param);
void Load_Square(struct wave_param *p);
void Load_Rectangular(struct wave_param *p);

uint16_t* Load_Sine(uint16_t *dac_samples_buffer, struct wave_param *param);
uint16_t* Load_Hav(uint16_t *dac_samples_buffer, struct wave_param *param);
uint16_t* Load_Triangular(uint16_t *dac_samples_buffer, struct wave_param *param);
uint16_t* Load_Sawtooth(uint16_t *dac_samples_buffer, struct wave_param *param);
uint16_t* Load_White(uint16_t *dac_samples_buffer, struct wave_param *param);
void SampleRate_Algorithm(struct wave_param *param);
