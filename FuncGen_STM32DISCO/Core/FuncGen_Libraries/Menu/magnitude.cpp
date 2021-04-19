/*
 * magnitude.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: Noto
 */

#include <magnitude.h>
#include "main.h"
#include "menu.h"
#include "math.h"
#include <vector>
#include <algorithm>

using namespace std;
const int lower_limit = 1;

magnitude::magnitude(int initial_value, int upper_limit)
{
    // TODO Auto-generated constructor stub
    this->digit_value = 0; //valor del digito menos significativo
    this->place_value = 0; //unidad a la cual la flecha apunta, el digito menos significativo
    this->upper_limit = upper_limit; //limite superior
    this->magnitude_value = initial_value; //valor inicial de la magnitud
    this->magnitude_vector = integer_to_array(this->magnitude_value); //convierto la magnitud a un array
    this->digit_value = *magnitude_vector.begin(); //valor del digito menos significativo
}

magnitude::~magnitude()
{
    // TODO Auto-generated destructor stub
}

int magnitude::refresh(
    int magnitude_value,
    int place_value,
    int digit_value,
    int digit_count)
{
    if (place_value != this->place_value)
    {
        std::reverse(this->magnitude_vector.begin(), this->magnitude_vector.end());
        this->place_value = place_value;
        TIM1->CNT = (this->magnitude_vector.at(place_value) << 2);//y fuerzo a que cnt sea del mismo valor para mantener el valor entre cambios de unidad
        std::reverse(this->magnitude_vector.begin(), this->magnitude_vector.end());
    }
    else
    {
        std::reverse(this->magnitude_vector.begin(), this->magnitude_vector.end());
        if (digit_value != this->magnitude_vector.at(place_value))
        {
            if ((digit_value >= this->magnitude_vector.at(place_value) && magnitude_value <= this->upper_limit))
            {
                if (digit_value == 9 && this->magnitude_vector.at(place_value) == 0)
                {
                    if ((this->magnitude_value - pow(10, place_value)) >= lower_limit)
                    {
                        std::reverse(this->magnitude_vector.begin(), this->magnitude_vector.end());
                        this->magnitude_value -= pow(10, place_value);
                        vector_fill(count_digit(this->magnitude_value), this->magnitude_value, digit_count);
                        return this->magnitude_value;
                    }
                }
                else
                {
                    if ((this->magnitude_value + pow(10, place_value)) <= this->upper_limit)
                        this->magnitude_vector.at(place_value) += 1;
                }
            }
            else
            {
                if (digit_value <=
                        this->magnitude_vector.at(place_value))
                {
                    if (digit_value == 0 && this->magnitude_vector.at(place_value) == 9)
                    {
                        if ((this->magnitude_value + pow(10, place_value)) <= this->upper_limit)
                        {
                            std::reverse(this->magnitude_vector.begin(), this->magnitude_vector.end());
                            this->magnitude_value += pow(10, place_value);
                            vector_fill(count_digit(this->magnitude_value), this->magnitude_value, digit_count);
                            return this->magnitude_value;
                        }
                    }
                    else
                    {
                        int aux = 0;
                        this->magnitude_vector.at(place_value) -= 1;
                        for (auto d : this->magnitude_vector)
                        {
                            if (d != 0)
                                aux = 1;
                        }
                        if (aux == 0)
                        {
                            *this->magnitude_vector.begin() = 1;
                        }
                    }
                }
            }
            TIM1->CNT = (this->magnitude_vector.at(place_value) << 2);//y fuerzo cnt al valor cambiado dentro de la funcion por si el usuario giró mas veces el encoder
            std::reverse(this->magnitude_vector.begin(), this->magnitude_vector.end());
            return (this->magnitude_value = array_to_integer());
        }
        std::reverse(this->magnitude_vector.begin(), this->magnitude_vector.end());
    }
    return this->magnitude_value;
}

vector<int> magnitude::integer_to_array(int x)
{
    vector<int> resultArray;
    while (true)
    {
        resultArray.insert(resultArray.begin(), x % 10);
        x /= 10;
        if (x == 0)
        {
            return resultArray;
        }
    }
}

int magnitude::array_to_integer(void)
{
    int result = 0;
    for (int d : this->magnitude_vector)
    {
        result = result * 10 + d;
    }
    return result;
}

int magnitude::count_digit(int n)
{
    return floor(log10(n) + 1);
}

void magnitude::vector_fill(
    int count, int value,
    int digit_count)
{
    int aux = 0;
    int diff = 0;
    if (count < digit_count)
    {
        diff = digit_count - count;
        for (int i = 0; i < diff; i++)
        {
            this->magnitude_vector[i] = 0;
        }
    }
    for (int i = (digit_count - 1); i >= diff; i--)
    {
        aux = value % 10;
        value /= 10;
        this->magnitude_vector[i] = aux;
    }
}
