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

void FSM_updatequeue();

void FSM_change_state();

void FSM_illuminateOrders();



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

    int floor = elevio_floorSensor();
    FSM_registerFloor( floor);

    bool stopBtn = elevio_stopButton();
    FSM_registerEmergency(stopBtn);

    bool ObsBtn = elevio_obstruction();
    FSM_registerObstruction(ObsBtn);

    m_FSM_elevatorVariables.door_open = false;

    m_FSM_elevatorVariables.requested_floor = NO_FLOOR;

    m_FSM_elevatorVariables.elevator_direction = ElevatorNewtral;

}  



void FSM_registerButton(int floor, int button, bool pressed){
    
    if(FSM_validate_button(floor,button)){
        int b_index = FSM_calculateIndex_ButtonPressed(floor, button);  
        m_FSM_elevatorVariables.button_pressed[b_index] = pressed;

    }
   
}




void FSM_registerFloor(int floor){
    if((floor != -1) && (floor > 0 ) && (floor < N_FLOORS) ){
        
        m_FSM_elevatorVariables.current_floorlevel = floor;

    }
}

void FSM_registerEmergency(bool stopBtn){
    m_FSM_elevatorVariables.emergency_stop = stopBtn;
}

void FSM_registerObstruction(bool ObsBtn){
    m_FSM_elevatorVariables.active_obstruction = ObsBtn;
}



void FSM_updateState(){

    FSM_updatequeue();
    m_FSM_elevatorVariables.requested_floor = queue_getNextfloor();
    
    elevio_floorIndicator(m_FSM_elevatorVariables.current_floorlevel);
    
    FSM_illuminateOrders( );


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

void FSM_updatequeue(){

    if(!m_FSM_elevatorVariables.emergency_stop){

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if(FSM_validate_button(f,b)){
                    
                
                    int b_index = FSM_calculateIndex_ButtonPressed(f,b);
                    
                    if(m_FSM_elevatorVariables.button_pressed[b_index]){//butten pressed
                        
                        Button_t pressedBtn = {f,b};

                        //can do this as it will copy the contex and not the pointer
                        queue_addOrder(&pressedBtn);
                    }

                }
            }           
        }

        queue_sortAndArrange(m_FSM_elevatorVariables.elevator_direction);

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
    printf("Floor level: %d \n", m_FSM_elevatorVariables.current_floorlevel);
    printf("Emergency stop: %d \n", m_FSM_elevatorVariables.emergency_stop);
    printf("Obstrucion: %d \n", m_FSM_elevatorVariables.active_obstruction);
    printf("Door open: %d \n", m_FSM_elevatorVariables.door_open);
    printf("Requested floor: %d \n", m_FSM_elevatorVariables.requested_floor);
    printf("Elev Dir: %d \n", m_FSM_elevatorVariables.elevator_direction);
    printf("\n");
    



}


void FSM_illuminateOrders(){
                    
    
    Button_t button;
     for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if(FSM_validate_button(f,b)){
                   
                    button.floor_level = f;
                    button.button_type = b;

                    if(queue_buttonExist(&button)){

                        elevio_buttonLamp(f, b, true);

                    } else{
                        elevio_buttonLamp(f, b, false);
                    }

                    
                }
            }           
        }
}