#define LINEA_1 0x00
#define LINEA_2 0x40
#define LINEA_3 0x14
#define LINEA_4 0x54

void init_lcd(void);
void cls_lcd(void);
void posic_lcd(char adress);
void lcd_wr(char datos);
void lcd_wr_data4bits (char datos);
void lcd_wr_instr4bits(char datos);
void wrchar(unsigned char dato);
void print (char cadena[]);
void print_shifted(char cadena[], int linea, int pos);
void clean_line(int line);
void print_int_dec(unsigned value);
void busy(uint16_t delay);
