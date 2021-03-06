#include "push_buttons.h"
#include <stdbool.h>

/* Esta biblioteca contiene la deteccion de los 2 pulsadores con el debouncing correspondiente */
int button_up, button_down, button_right, button_left;
bool clear_flag = false;

void button_action(uint16_t Button)
{
    uint8_t state;
    switch (Button)
    {
    case DOWN:
        state = HAL_GPIO_ReadPin(GPIOD, BUTTON_DOWN_Pin);
        if (state == GPIO_PIN_SET)
        {
            button_down = DOWN;
            clear_flag = false;
        }
        else
        {
            button_down = NONE;
        }
        break;
    case UP:
        state = HAL_GPIO_ReadPin(GPIOD, BUTTON_UP_Pin);
        if (state == GPIO_PIN_SET)
        {
            button_up = UP;
            clear_flag = false;
        }
        else
        {
            button_up = NONE;
        }
        break;
    default:
        //button = NONE;
        break;
    }
}
