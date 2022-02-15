/**
 * @file
 * @brief Header file for struct order
 */


#pragma once


#include "Button.h"


typedef struct{
    int floor_destination;
    Button_t* p_orderButton;
}Order_t;
