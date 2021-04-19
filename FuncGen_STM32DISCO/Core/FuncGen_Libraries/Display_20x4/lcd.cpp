#include "main.h"
#include "lcd.h"

#define DISPLAY_PORT GPIOD->ODR
#define RS 0x00000010
#define E  0x00000020
extern int ldc_init_flag;
extern int lcd_wr_flag;
extern int lcd_posic_flag;
extern int lcd_wr_instr4bits_flag;
extern int aux_aux;
extern int lcd_cnt;
extern char aux_address;
unsigned char aux;
int test_flag = 1;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    switch(lcd_posic_flag)
    {
    case 1:
        if(lcd_cnt++ >= 20)
        {
            lcd_wr_instr4bits(aux_address | 0x80);
            lcd_cnt = 0;
            lcd_posic_flag = 2;
        }
        break;
    case 2:
        if(lcd_cnt++ >= 10)
        {
            lcd_cnt = 0;
            lcd_posic_flag = 0;
        }
        break;
    }

    switch(ldc_init_flag)
    {
    case 1:
        lcd_wr(0x30); //30
        ldc_init_flag = 2;
        break;
    case 2:
        lcd_wr(0x30); //30
        ldc_init_flag = 3;
        break;
    case 3:
        lcd_wr(0x30); //30
        ldc_init_flag = 4;
        break;
    case 4:
        lcd_wr(0x20); //30
        ldc_init_flag = 5;
        break;
    case 5:
        lcd_wr_instr4bits(0x28);
        ldc_init_flag = 6;
        break;
    case 6:
        lcd_wr_instr4bits(0x06);
        ldc_init_flag = 7;
        break;
    case 7:
        lcd_wr_instr4bits(0x0c);
        ldc_init_flag = 8;
        break;
    case 8:
        lcd_wr_instr4bits(0x01);
        ldc_init_flag = 0;
        break;
    }
    switch(lcd_wr_flag)
    {
    case 1:
        aux_aux >>= 4;
        DISPLAY_PORT &= ~0x0000003F;
        DISPLAY_PORT |= aux_aux;
        DISPLAY_PORT &= ~RS;
        DISPLAY_PORT |= E;
        lcd_wr_flag = 2;
        break;
    case 2:
        if(lcd_cnt >= 5)
        {
            lcd_cnt = 0;
            lcd_wr_flag = 0;
        }
        break;
    }

    switch(lcd_wr_instr4bits_flag)
    {
    case 1:
        lcd_wr_instr4bits_flag = 2;
        lcd_cnt = 0;
        aux = aux_aux;
        aux >>= 4;
        aux &= 0x0f;
        DISPLAY_PORT &= ~0x0000003F;
        DISPLAY_PORT |= aux;
        DISPLAY_PORT |= RS;
        DISPLAY_PORT |= E;
        break;
    case 2:
        if(lcd_cnt++>=4)
        {
            lcd_cnt = 0;
            lcd_wr_instr4bits_flag = 3;
            DISPLAY_PORT &= ~E;
        }
        break;
    case 3:
        lcd_wr_instr4bits_flag = 4;
        aux = aux_aux;
        aux &= 0x0f;
        DISPLAY_PORT &= ~0x0000003F;
        DISPLAY_PORT |= aux;
        DISPLAY_PORT |= RS;
        DISPLAY_PORT |= E;
        break;
    case 4:
        lcd_wr_instr4bits_flag = 5;
        lcd_cnt = 0;
        DISPLAY_PORT &= ~E;
        break;
    case 5:
        if(lcd_cnt++>=4)
        {
            lcd_cnt = 0;
            lcd_wr_instr4bits_flag = 0;
        }
        break;
    }
}


void lcd_wr_data4bits(char datos)
{
    aux_aux = datos;
    lcd_wr_instr4bits_flag = 1;
}
void lcd_wr(char datos)
{
    aux_aux = datos;
    lcd_wr_flag = 1;
}

void lcd_wr_instr4bits(char datos)
{
    aux = datos;
    aux >>= 4;
    aux &= 0x0f;
    DISPLAY_PORT &= ~0x0000003F;
    DISPLAY_PORT |= aux;
    DISPLAY_PORT &= ~RS;
    DISPLAY_PORT |= E;
    DISPLAY_PORT &= ~E;
    aux = datos;
    aux &= 0x0f;
    DISPLAY_PORT &= ~0x0000003F;
    DISPLAY_PORT |= aux;
    DISPLAY_PORT &= ~RS;
    DISPLAY_PORT |= E;
    DISPLAY_PORT &= ~E;
}


void init_lcd()
{
    ldc_init_flag = 1;
}

void cls_lcd(void)
{
    lcd_wr_instr4bits(0x01);
}

void posic_lcd(char address)
{
    aux_address = address;
    lcd_posic_flag = 1;
}

void wrchar(unsigned char dato)
{
    lcd_wr_data4bits(dato);
}

void print(char cadena[])
{
    char i = 0;
    while (cadena[i] != '\0')
    {
        if(lcd_wr_instr4bits_flag == 0 && lcd_posic_flag == 0)
        {
            wrchar(cadena[i++]);
        }
    }
}

void cursor_normal(void)
{
    lcd_wr_instr4bits(0x0c);  //cursor normal
}

void cursor_titilante(void)
{
    lcd_wr_instr4bits(0x0d);  //cursor titilante
}

void print_int_dec(unsigned value) //de "00" a "65535" (int)
{
    unsigned char dmil = 0, umil = 0, centena = 0, decena = 0, unidad = 0;
    unidad = value % 0x0a;
    decena = (value / 10) % 0x0a;
    centena = (value / 100) % 0x0a;
    umil = (value / 1000) % 0x0a;
    dmil = (value / 10000) % 0x0a;
    if (dmil)
    {
        wrchar(dmil | 0x30);
    }
    if (umil)
    {
        wrchar(umil | 0x30);
    }
    if (centena)
    {
        wrchar(centena | 0x30);
    }
    wrchar(decena | 0x30);
    wrchar(unidad | 0x30);
}

void print_hex(unsigned char dato)
{
    unsigned char aux;
    aux = dato;
    aux &= 0xf0;
    aux >>= 4;
    if (aux > 9)
    {
        aux += 0x37;
    }
    else
    {
        aux += 0x30;
    }
    wrchar(aux);
    aux = dato;
    aux &= 0x0f;
    if (aux > 9)
    {
        aux += 0x37;
    }
    else
    {
        aux += 0x30;
    }
    wrchar(aux);
}

void print_int_hex(unsigned int dato)
{
    print_hex(dato >> 8);
    print_hex(dato & 0xff);
}

void print_shifted(char cadena[], int linea, int pos)
{
    int l = 0;
    if (linea == 1)
    {
        l = LINEA_1;
    }
    else if (linea == 2)
    {
        l = LINEA_2;
    }
    else if (linea == 3)
    {
        l = LINEA_3;
    }
    else
    {
        l = LINEA_4;
    }
    posic_lcd(l + pos);
    print(cadena);
}

void clean_line(int line)
{
    print_shifted((char*)"                    ", line, 0);
}
