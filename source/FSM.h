/**
 * @file
 * @brief Headerfile for Finite State Machine
 */


#pragma once

#include "defines.h"
#include "queue.h"
#include "elevatordirection.h"



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






typedef struct{
    int current_floorlevel; //oppdateres i main
    bool emergency_stop;    //fra main
    bool active_obstruction;    // fra main
    bool door_open;             // fikses i change of state
    int requested_floor;        //updateres i updateState (OBS!! CAN BE NO FLOOR)
    ElevatorDirection elevator_direction;   // updates i change og state
    int button_pressed[NUMBER_OF_BUTTONS];  // updateres i main

}ElevatorVariables;






void FSM_init();






void FSM_registerButton(int floor, int button, bool pressed);

void FSM_registerFloor(int floor);

void FSM_registerEmergency(bool stopBtn);

void FSM_registerObstruction(bool ObsBtn);



void FSM_updateState();

//void FSM_change_state();


void FSM_cleanUP();



void FSM_printButtons();
