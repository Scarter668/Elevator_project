/**
 * @file
 * @brief Implementation file for queue file
 */


#include "queue.h"
#include <assert.h>



static Order_queue_t m_order_queue;



void queue_init(){
    m_order_queue.p_firstOrder = NULL;
    m_order_queue.p_lastOrder = NULL;
    m_order_queue.size = 0;
}

bool queue_orderExist(Button_t* button){
    assert(button != NULL);
    if(m_order_queue.size >0){

        Order_t* p_order = m_order_queue.p_firstOrder;
        while(p_order != NULL ){

            if(button_equalButtons(p_order->p_orderButton, button)){
                //printf("Was true\n");
                return true;
            }

            p_order = p_order->nextOrder;
        }
    }
    return false;
}


void queue_createOrder(Button_t* button){
    
    
    if( !queue_orderExist(button)){ //order not found
        //debug
        printf("I am in order\n");
        

        //have to implemetent a check if malloc returns NULL
        //copy the context of button 
        Button_t* p_button = malloc(sizeof(Button_t));
        p_button->button_type = button->button_type;
        p_button->floor_level_from = button->floor_level_from;


        Order_t* p_order = malloc(sizeof(Order_t)); // = {button, NULL, NULL};
        p_order->p_orderButton = p_button;
        p_order->nextOrder = NULL;
        p_order->prevOrder = NULL; 
        

        if (m_order_queue.size == 0){
            m_order_queue.p_firstOrder = p_order;
            m_order_queue.p_lastOrder = p_order;
            m_order_queue.size = 1;

        } else{
            //trenger her selektiv logikk

            //for now
            p_order->prevOrder = m_order_queue.p_lastOrder;
            m_order_queue.p_lastOrder->nextOrder = p_order;
            m_order_queue.p_lastOrder  = p_order;
            m_order_queue.size++;
            
            printf("Made order order\n");

        }

    }

}

void queue_print_queue(){
    Order_t* ord = m_order_queue.p_firstOrder;
    while ( ord!= NULL){
        printf("THE order is from floor %d\n",ord->p_orderButton->floor_level_from);
        ord = ord->nextOrder;
    }
    printf("There was %d orders", m_order_queue.size);
    
}


void queue_clear_all(){
    
    Order_t* next; 
    while(m_order_queue.p_firstOrder){
        
        next = m_order_queue.p_firstOrder->nextOrder;
        free(m_order_queue.p_firstOrder);
        m_order_queue.p_firstOrder = next;
    }
    m_order_queue.size = 0;
}