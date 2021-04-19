/*
 * magnitude.h
 *
 *  Created on: Dec 28, 2020
 *      Author: Noto
 */

#ifndef FUNCGEN_LIBRARIES_MENU_MAGNITUDE_H_
#define FUNCGEN_LIBRARIES_MENU_MAGNITUDE_H_

#include <iostream>
#include <vector>

using namespace std;

class magnitude
{
public:
    vector<int> magnitude_vector;
    int magnitude_value;
    int digit_value;
    int place_value;
    int upper_limit;
public:
    magnitude(int initial_limit, int upper_limit);
    vector<int> integer_to_array(int);
    int array_to_integer(void);
    int refresh(int magnitude_value, int place_value, int digit_value, int digit_count);
    int count_digit(int n);
    void vector_fill(int count, int value, int digit_count);
    virtual ~magnitude();
};

#endif /* FUNCGEN_LIBRARIES_MENU_MAGNITUDE_H_ */
