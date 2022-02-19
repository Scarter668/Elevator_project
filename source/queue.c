/**
 * @file
 * @brief Implementation file for queue file
 */


#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


static Order_queue_t m_order_queue;

//hjelpefunksjoner
void queue_freeOrder(Order_t* order);

void queue_insertOrderInFront(Order_t* p_insert, Order_t* p_infront);

void queue_appendOrder(Order_t* p_order);

void queue_deleteOrder(Order_t* p_order);

void queue_removeOrder(Order_t* p_order);




void queue_init(){

    m_order_queue.p_firstOrder = order_createOrder(NULL);
    m_order_queue.p_end = m_order_queue.p_firstOrder;
    m_order_queue.size = 0;
}

// Order_queue_t* queue_getQueuePtr(){
//     return &m_order_queue;
// }


void queue_addOrder(Button_t* button){
    
    
    if( !queue_buttonExist(button)){ //order not found
        //debug
        printf("I am in order\n");
        

        //have to implemetent a check if malloc returns NULL
        //copy the context of button 
        Button_t* p_button = button_copyButton(button);

        Order_t* p_order = order_createOrder(p_button);
        

        //trenger her selektiv logikk

       //for now
        queue_appendOrder(p_order);
            
        printf("Made order order\n");

        

    }

}

void queue_removeOrders(int floor){



    //printf("REMOVED ORDER FROM FLOOR %d\n", floor);


    //printf("Before removal\n");
    queue_print_queue();
    Order_t* order = m_order_queue.p_firstOrder;
    while(order != m_order_queue.p_end){
        
        
        if(order->p_orderButton->floor_level == floor){ ///found a match
            
            Order_t* foundMatch = order;
            order = order->nextOrder;
            queue_deleteOrder(foundMatch);
        
        } else{ //did not find a match

            order = order->nextOrder;
        }
        
    }
    // printf("After Removal update:\n");
    // queue_print_queue();
    // printf("END\n");

}

void queue_sortAndArrange(ElevatorDirection dir){
    
    //have to fill with sorting

    
}
    

int queue_getNextfloor(){
    if(m_order_queue.size == 0){
        return NO_FLOOR;
    }
    return m_order_queue.p_firstOrder->p_orderButton->floor_level;
}

bool queue_buttonExist(Button_t* button){
    assert(button != NULL);
    if(m_order_queue.size >0){

        Order_t* p_order = m_order_queue.p_firstOrder;
        while(p_order != m_order_queue.p_end){

            if(button_equalButtons(p_order->p_orderButton, button)){
                //printf("Was true\n");
                return true;
            }

            p_order = p_order->nextOrder;
        }
    }
    return false;
}

void queue_print_queue(){
    Order_t* ord = m_order_queue.p_firstOrder;
    while ( ord != m_order_queue.p_end){
        printf("THE order is from floor %d\n",ord->p_orderButton->floor_level);
        ord = ord->nextOrder;
    }
    printf("There was %d orders\n\n", m_order_queue.size);
    
}



void queue_clear_all(){
    
    Order_t* next; 
    while(m_order_queue.p_firstOrder != m_order_queue.p_end){
        
        next = m_order_queue.p_firstOrder->nextOrder;
        queue_deleteOrder(m_order_queue.p_firstOrder);
        m_order_queue.p_firstOrder = next;
    }
    m_order_queue.size = 0;
}



void queue_freeOrder(Order_t* order){

    free(order->p_orderButton);
    free(order);
}



void queue_insertOrderInFront(Order_t* p_insert, Order_t* p_infront){

    assert(p_insert);
    assert(p_infront);
    Order_t* prev = p_infront->prevOrder;

    //printf("before adding order %d\n", p_insert->p_orderButton->floor_level); 
    if(prev ){
        prev->nextOrder = p_insert;
        p_insert->prevOrder = prev;

        p_insert->nextOrder = p_infront;
        p_infront->prevOrder = p_insert;

    } else{

        p_insert->nextOrder = p_infront;
        p_infront->prevOrder = p_insert;
        p_insert->prevOrder = NULL;
        
        
        m_order_queue.p_firstOrder = p_insert; 
        //printf("Added order %d\n", p_insert->p_orderButton->floor_level); 
    }
    m_order_queue.size++;

}


void queue_appendOrder(Order_t* p_order){
    assert(p_order);
    queue_insertOrderInFront(p_order,m_order_queue.p_end);
}

void queue_deleteOrder(Order_t* p_order){

    queue_removeOrder(p_order);
    
    queue_freeOrder(p_order);

}

void queue_removeOrder(Order_t* p_order){
    if(p_order && p_order != m_order_queue.p_end){

        Order_t* prev = p_order->prevOrder;
        Order_t* next = p_order->nextOrder;

        if(p_order == m_order_queue.p_firstOrder){
            m_order_queue.p_firstOrder = next;
        }

        if(prev){
            prev->nextOrder = next;
        }
        if(next){
            next->prevOrder = prev;
        }
        p_order->nextOrder = NULL;
        p_order->prevOrder = NULL;
        m_order_queue.size--;
    }
}
