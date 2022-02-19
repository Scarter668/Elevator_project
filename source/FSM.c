/**
 * @file
 * @brief Implementation file for FSM.h
 */


#include "FSM.h"
#include "driver/elevio.h"
#include "stdio.h"
#include "timer.h"



static FSM_states m_FSM_currentState;

static FSM_states m_FSM_memoryState;


static ElevatorVariables m_FSM_elevatorVariables; 


bool FSM_validate_button(int floor, int button);

int FSM_calculateIndex_ButtonPressed(int floor, int button);

void FSM_updatequeue();

void FSM_change_state();

void FSM_illuminateOrders();

bool FSM_verifyAndDealWithStopBtn();

void FSM_deleteAllOrders();

void FSM_setDoorOpen(bool doorstate);

void FSM_stopAndUpdateIfArrived();









void FSM_init(){
    elevio_init();
    timer_init();
    queue_init();

    m_FSM_currentState = initializing;
    m_FSM_memoryState = m_FSM_currentState;
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


    if(floor == NO_FLOOR){
        elevio_motorDirection(DIRN_UP);
    }
    

    FSM_registerFloor( floor);
    m_FSM_elevatorVariables.virtual_floorlevel = floor;

    bool stopBtn = elevio_stopButton();
    FSM_registerEmergency(stopBtn);

    bool ObsBtn = elevio_obstruction();
    FSM_registerObstruction(ObsBtn);

    m_FSM_elevatorVariables.door_open = false;

    m_FSM_elevatorVariables.requested_floor = NO_FLOOR;

    m_FSM_elevatorVariables.elevator_direction = ElevatorNewtral;

    FSM_change_state();

}  



void FSM_registerButton(int floor, int button, bool pressed){
    
    if(FSM_validate_button(floor,button)){
        int b_index = FSM_calculateIndex_ButtonPressed(floor, button);  
        m_FSM_elevatorVariables.button_pressed[b_index] = pressed;

    }
   
}




void FSM_registerFloor(int floor){
    if((floor != NO_FLOOR) && (floor >= 0 ) && (floor < N_FLOORS) ){
        
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
    
    //queue_print_queue();
    //FSM_printButtons();
    if(!m_FSM_elevatorVariables.emergency_stop){

        FSM_updatequeue();
        m_FSM_elevatorVariables.requested_floor = queue_getNextfloor();

        m_FSM_elevatorVariables.virtual_floorlevel = (float) m_FSM_elevatorVariables.current_floorlevel;

        if(m_FSM_elevatorVariables.current_floorlevel != NO_FLOOR){

            elevio_floorIndicator(m_FSM_elevatorVariables.current_floorlevel);
        }
        
    }
    
    FSM_illuminateOrders();

    FSM_change_state();

    


}


void FSM_change_state(){

    

    switch (m_FSM_currentState)
    {
    case initializing:
        {
                
            int floor = elevio_floorSensor();
            if(floor != NO_FLOOR){
                elevio_motorDirection(DIRN_STOP);
                FSM_registerFloor( floor);
                m_FSM_currentState = idle;
            }
        }
        break;

    case idle:

        if(FSM_verifyAndDealWithStopBtn()){
            break;
        }

        if(m_FSM_elevatorVariables.door_open && m_FSM_elevatorVariables.active_obstruction){
            m_FSM_currentState = obstructionWait;
            m_FSM_memoryState = idle;

            break;
        }

        if(timer_isActive() && timer_isTimeout()){
            
            FSM_setDoorOpen(false);
            
        }

        if(m_FSM_elevatorVariables.requested_floor != NO_FLOOR){
            
            m_FSM_currentState = readying;
            
        }



        break;

    case readying:
        if(FSM_verifyAndDealWithStopBtn()){
            break;
        }
        if(m_FSM_elevatorVariables.door_open && m_FSM_elevatorVariables.active_obstruction){
            m_FSM_currentState = obstructionWait;
            break;
        }

        if(m_FSM_elevatorVariables.door_open){
            
            FSM_setDoorOpen(false);
        }
         

        
        float virt_floor = m_FSM_elevatorVariables.virtual_floorlevel;
        float to_floor = (float) m_FSM_elevatorVariables.requested_floor;
        if(virt_floor > to_floor ){

            elevio_motorDirection(DIRN_DOWN);
            m_FSM_elevatorVariables.virtual_floorlevel -= 0.5;
            m_FSM_currentState = elevatorDown;

        } else if( virt_floor == to_floor){
            printf("virt_floor: %f, to_floor: %f\n",virt_floor,to_floor);
            FSM_setDoorOpen(true);
            timer_start();
            queue_removeOrders(to_floor);
            m_FSM_currentState = floorArrived;
        } else{
            
            elevio_motorDirection(DIRN_UP);
            m_FSM_elevatorVariables.virtual_floorlevel += 0.5;
            m_FSM_currentState = elevatorUp;

        }

        break;
    
    case elevatorDown: //3
        if(FSM_verifyAndDealWithStopBtn()){
            break;
        }
        

        FSM_stopAndUpdateIfArrived();

        
        break;
    
    case elevatorUp: //4
        if(FSM_verifyAndDealWithStopBtn()){
            break;
        }

        


        FSM_stopAndUpdateIfArrived();


        break;

    case floorArrived: //5
        if(FSM_verifyAndDealWithStopBtn()){
            break;
        }
    

        if(m_FSM_elevatorVariables.door_open && m_FSM_elevatorVariables.active_obstruction){
            m_FSM_currentState = obstructionWait;
            m_FSM_memoryState = floorArrived;
            break;
        }

        

        if(timer_isActive() && timer_isTimeout()){
            
            FSM_setDoorOpen(false);
            
            if(m_FSM_elevatorVariables.requested_floor != NO_FLOOR){
                
                m_FSM_currentState = readying;

            } else{

                m_FSM_currentState = idle;
            }

            
        }


        break;

    case obstructionWait: //6
        if(FSM_verifyAndDealWithStopBtn()){
            break;
        }

    
        
        if(!m_FSM_elevatorVariables.active_obstruction){
            
            timer_start();
            m_FSM_currentState = m_FSM_memoryState;
        }
         

        break;
    
    case emergencyStop: //7

        if(!m_FSM_elevatorVariables.emergency_stop){
            
            if(m_FSM_elevatorVariables.door_open){
                FSM_setDoorOpen(false);
                timer_start();
            }
            elevio_stopLamp(false);

            m_FSM_currentState = idle;
        }

        break;



    default:
        break;
    }

    printf("I AM IN STATE %d\n", m_FSM_currentState);

}

void FSM_updatequeue(){

    if(!m_FSM_elevatorVariables.emergency_stop){ //ignore request

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if(FSM_validate_button(f,b)){
                    
                
                    int b_index = FSM_calculateIndex_ButtonPressed(f,b);
                    

                    if(m_FSM_elevatorVariables.button_pressed[b_index]){//butten pressed = requested floor
                        
                        //if not (at requested floor, and state is at arrived, and door is open) 
                        if(!((m_FSM_elevatorVariables.current_floorlevel == f) && (m_FSM_currentState == floorArrived) && m_FSM_elevatorVariables.door_open)){
                            Button_t pressedBtn = {f,b};

                            //can do this as it will copy the contex and not the pointer
                            queue_addOrder(&pressedBtn);
                        
                        }
                    }

                }
            }           
        }

        queue_sortAndArrange(m_FSM_elevatorVariables.elevator_direction);

    }


}




void FSM_cleanUP(){
    //

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
    printf("State: %d \n", m_FSM_currentState);
    printf("Floor level: %d \n", m_FSM_elevatorVariables.current_floorlevel);
    printf("Virtual floor level: %f \n", m_FSM_elevatorVariables.virtual_floorlevel);
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

bool FSM_verifyAndDealWithStopBtn(){

    if(m_FSM_elevatorVariables.emergency_stop){
        
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(true);
        FSM_deleteAllOrders();
        timer_stop();

        float virt_floor = m_FSM_elevatorVariables.virtual_floorlevel;
        float curr_floor = (float) m_FSM_elevatorVariables.current_floorlevel;
        if( virt_floor == curr_floor){
            FSM_setDoorOpen(true);
        }
        printf(" virt floor: %f, curr_floor %f",virt_floor,curr_floor);
        m_FSM_currentState = emergencyStop;
        return true;
    }
    return false;
}

void FSM_deleteAllOrders(){
    queue_clear_all();
    m_FSM_elevatorVariables.requested_floor = queue_getNextfloor();
}

void FSM_setDoorOpen(bool doorstate){
    m_FSM_elevatorVariables.door_open = doorstate;
    elevio_doorOpenLamp(doorstate);
}

void FSM_stopAndUpdateIfArrived(){

    int curr_floor = m_FSM_elevatorVariables.current_floorlevel;
    int to_floor =  m_FSM_elevatorVariables.requested_floor;
    if(curr_floor == to_floor){
        elevio_motorDirection(DIRN_STOP);
        FSM_setDoorOpen(true);
        timer_start();
        //printf("cf %d, to_f %d \n ",curr_floor,to_floor);
        queue_removeOrders(curr_floor);
        m_FSM_elevatorVariables.virtual_floorlevel = (float) curr_floor;
        m_FSM_currentState = floorArrived;
    }


}