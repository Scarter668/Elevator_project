/**
 * @file
 * @brief Headerfile for Finite State Machine
 */


#pragma once

#include "defines.h"
#include "queue.h"


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



typedef enum ElevatorDirection{
    ElevatorUP = 0,
    ElevatorDown,
    ElevatorNewtral
} ElevatorDirection;



typedef struct{
    int current_floorlevel;
    bool emergency_stop;
    bool active_obstruction;
    bool door_open;
    int requested_floor;
    ElevatorDirection elevator_direction;
    int button_pressed[NUMBER_OF_BUTTONS];

}ElevatorVariables;






void FSM_init();


void FSM_change_state();



void FSM_registerButton(int floor, int button, bool pressed);


void FSM_cleanUP();



void FSM_printButtons();
