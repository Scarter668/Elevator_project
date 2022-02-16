/**
 * @file
 * @brief Header file for struct linkedList
 */


#pragma once

#include "order.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * @brief Definerd @c bool , @c true , and @c false
 * in order to increase readability
 */
#define bool int
#define true 1
#define false 0


typedef struct Order_queue_t{
    Order_t* p_firstOrder;
    Order_t* p_lastOrder;
    int size;

}Order_queue_t;





void queue_init();

void queue_createOrder(Button_t* button);


//test func
void queue_print_queue();


void queue_clear_all();

