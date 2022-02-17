/**
 * @file
 * @brief Implementation for order file
 */

#include "order.h"
#include <stdlib.h>


Order_t* order_createOrder(Button_t* button){
    
  
    Order_t* p_order = malloc(sizeof(Order_t)); // = {button, NULL, NULL};
    p_order->p_orderButton = button;
    p_order->nextOrder = NULL;
    p_order->prevOrder = NULL; 
    return p_order;
    
}


