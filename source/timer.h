/**
 * @file
 * @brief Headerfile for timer
 */

#pragma once
//#include <pthread.h>
//#include <unistd.h>

#include <time.h>


/**
 * @brief Definerd @c bool , @c true , and @c false
 * in order to increase readability
 */
#define bool int
#define true 1
#define false 0

/**
 * @brief The timeout lenght in seconds
 */
#define TIMEOUT_LENGHT 3.0

//static pthread_t newthread;
//void* printHello(void* arg);
//void start_printing();
//bool timeout;


/**
 * @brief Keep track of wheter or not there is an active timer
 */
static bool m_active_timer;

/**
 * @brief Stores the time the timer was started to be combared with @p TIMEOUT_LENGHT
 */
static time_t m_clock_start;



/**
 * @brief Starts the timer by regitering the current time.
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

