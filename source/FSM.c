/**
 * @file
 * @brief Implementation file for FSM.h
 */


#include "FSM.h"
#include "driver/elevio.h"
#include "stdio.h"



static FSM_states m_FSM_currentState;

static ElevatorVariables m_FSM_elevatorVariables; 


bool FSM_validate_button(int floor, int button);

int FSM_calculateIndex_ButtonPressed(int floor, int button);


void FSM_init(){
    m_FSM_currentState = initializing;
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){

            if(FSM_validate_button(f,b)){

                int b_index = FSM_calculateIndex_ButtonPressed(f,b);

                bool pressed = elevio_callButton(f,b);
                m_FSM_elevatorVariables.button_pressed[b_index] = pressed;
            }
        }           
    } 
}  


void FSM_registerButton(int floor, int button, bool pressed){
    
    int b_index = FSM_calculateIndex_ButtonPressed(floor, button);
    m_FSM_elevatorVariables.button_pressed[b_index] = pressed;
}


void FSM_change_state(){



    switch (m_FSM_currentState)
    {
    case initializing:
        
        break;

    case idle:
        break;

    case readying:
        break;
    
    case elevatorDown:
        break;
    
    case elevatorUp:
        break;

    case floorArrived:
        break;

    case obstructionWait:
        break;
    
    case emergencyStop:
        break;

    default:
        break;
    }



}


void FSM_cleanUP(){
    // for(int i = 0; i < NUMBER_OF_BUTTONS; i++){
    //     free(m_FSM_elevatorVariables.button_pressed[i]);
    // }
    // free(m_FSM_elevatorVariables.button_pressed);

}


bool FSM_validate_button(int floor, int button){
    
    if((floor == 3) && (button == BUTTON_HALL_UP) ) return false;
    if((floor == 0) && (button == BUTTON_HALL_DOWN) ) return false;

    return true;
}

int FSM_calculateIndex_ButtonPressed(int floor, int button){
    int ind;
    switch (button)
    {
    case BUTTON_HALL_UP:
        ind = floor;
        break;

    case BUTTON_HALL_DOWN:
        ind = N_BUTTONS + floor - 1;
        break;

    case BUTTON_CAB:
        ind = N_BUTTONS*2 + floor;
        break;
    }
    return ind;
}

void FSM_printButtons(){

    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){

            if(FSM_validate_button(f,b)){
                
                int b_index = FSM_calculateIndex_ButtonPressed(f,b);
                printf("THE button is from floor %d and the pressed statet was: %d\n",f, m_FSM_elevatorVariables.button_pressed[b_index]);
            }
        }           
    }
    for(int i = 0; i < NUMBER_OF_BUTTONS; i++){
        
    }
}
