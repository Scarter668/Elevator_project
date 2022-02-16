/**
 * @file
 * @brief Header file for struct Button
 */

#pragma once


#include "driver/elevio.h"
/**
 * @brief Definerd @c bool , @c true , and @c false
 * in order to increase readability
 */
#define bool int
#define true 1
#define false 0

typedef struct Button_t{
    
    int floor_level_from;
    ButtonType  button_type;

}Button_t;


bool button_equalButtons(Button_t* first, Button_t* second);
