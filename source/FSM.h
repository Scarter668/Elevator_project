/**
 * @file
 * @brief Headerfile for Finite State Machine
 */


#pragma once

/**
 * @brief Definerd @c bool , @c true , and @c false
 * in order to increase readability
 */
#define bool int
#define true 1
#define false 0



typedef enum {
    initializing = 0,
    idle,
    readying,
    elevatorDown,
    elevatorUp,
    floorArrived,
    obstructionWait,
    emergencyStop
}FSM_states;

typedef enum OrderDirection{
    orderUP = 0,
    orderDown
} OrderDirection;




static FSM_states m_FSM_currentState;


typedef struct{
    /* data */
}elevatorVariables;

static bool m_activeObstruction;






void FSM_init();


void change_state();

