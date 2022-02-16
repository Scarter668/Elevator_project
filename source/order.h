/**
 * @file
 * @brief Header file for struct order
 */


#pragma once


#include "button.h"



typedef struct Order_t{
    Button_t* p_orderButton;

    struct Order_t* nextOrder;
    struct Order_t* prevOrder;
}Order_t;





