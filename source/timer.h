/**
 * @file
 * @brief Headerfile for timer
 */

#pragma once
//#include <pthread.h>
//#include <unistd.h>

#include <time.h>
#include "defines.h"



/**
 * @brief The timeout lenght in seconds
 */
#define TIMEOUT_LENGHT 3.0

//static pthread_t newthread;
//void* printHello(void* arg);
//void start_printing();
//bool timeout;



/**
 * @brief Starts the timer by registering the current time.
 */
void timer_start();


/**
 * @brief Checks if a timer is active
 *
 * @return true or false depending on @p m_active_timer
 */
bool timer_isActive();

/**
 * @brief Checks if the timer has timed out, and deactivates it if so.
 *
 * @return true or false depending on the duration of the timer
 */
bool timer_isTimeout();


/**
 * @brief Initiates the static variables used by timer
 */
void timer_init();


/**
 * @brief Stop timer by setting the timer to false.
 */
void timer_stop();
