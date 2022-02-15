/**
 * @file
 * @brief Header file for struct linkedList
 */


#pragma once

#include "order.h"

typedef struct{
    Order_t* p_currOrder;
    Order_t* p_nextOrder;
    Order_t* p_prevOrder;
}node_t;

typedef struct{
    node_t* p_frontNode;
    node_t* p_endNode;
    int size;
}Order_que_t;






