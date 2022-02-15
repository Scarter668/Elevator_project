/**
 * @file
 * @brief Implementation file for FSM.h
 */


#include "FSM.h"


void FSM_init(){
    m_FSM_currentState = initializing;
}




void change_state(){



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
