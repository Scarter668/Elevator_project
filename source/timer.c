/**
 * @file
 * @brief Implementation file for timer.h
 */


#include "timer.h"



// void* printHello(void* arg){
//     for (int i=0; i<8; i++){
//         printf("DEtter er en test\n");
//         sleep(10);
//     }
//     return  NULL;

// }

// void start_printing(){
//     pthread_create(&newthread, NULL, printHello, NULL);
// }


/**
 * @brief Keep track of wheter or not there is an active timer
 */
static bool m_active_timer;

/**
 * @brief Stores the time the timer was started to be combared with @p TIMEOUT_LENGHT
 */
static time_t m_clock_start;



void timer_start(){

    m_active_timer = true;
    //timeout = false;
    m_clock_start = time(NULL);
}

void timer_stop(){
    m_active_timer = false;
}

bool timer_isActive(){
    return m_active_timer;
}

bool timer_isTimeout(){
    if(m_active_timer){

        if(difftime(time(NULL) ,m_clock_start) >= TIMEOUT_LENGHT){
            timer_stop();
            return true;
        }
    }

    return false;
}

void timer_init(){
    m_active_timer = false;
    m_clock_start = time(NULL);
};


