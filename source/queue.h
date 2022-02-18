/**
 * @file
 * @brief Header file for struct linkedList
 */


#pragma once

#include "order.h"


#include "defines.h"
#include "elevatordirection.h"

typedef struct Order_queue_t{
    Order_t* p_firstOrder;
    Order_t* p_end;
    int size;

}Order_queue_t;





void queue_init();

//Order_queue_t* queue_getQueuePtr();

void queue_addOrder(Button_t* button);

void queue_sortAndArrange(ElevatorDirection dir);

int queue_getNextfloor();

bool queue_buttonExist(Button_t* button);


//test func
void queue_print_queue();


void queue_clear_all();

