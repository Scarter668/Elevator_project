

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


void start_timer(){

    m_active_timer = true;
    //timeout = false;
    m_clock_start = time(NULL);
}

void stop_timer(){
    m_active_timer = false;
}

bool timer_active(){
    return m_active_timer;
}

bool timer_is_timeout(){
    if(m_active_timer){
        
        //double diff = difftime(time(NULL),clock_start);
        //printf("Difftime ney %f\n", diff);
        if( difftime(time(NULL) ,m_clock_start) >= TIMEOUT_LENGHT){
            stop_timer();
            //timeout = true;
            //double diff = difftime(clock_start, time(NULL));
            //printf("Difftime yey%f\n", diff);
            return true;
        }
    }

    return false;
}


