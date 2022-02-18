/**
 * @file
 * @brief Header file for struct Button
 */

#pragma once

#include "defines.h"

#include "driver/elevio.h"




typedef struct Button_t{
    
    int floor_level;
    ButtonType  button_type;

}Button_t;


bool button_equalButtons(Button_t* first, Button_t* second);


Button_t* button_copyButton(Button_t* button);


Button_t* button_createButton(int floor, int button);
