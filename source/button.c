/**
 * @file
 * @brief Implementation file for queue file
 */


#include "button.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>




bool button_equalButtons(Button_t* first, Button_t* second){
    //debug
    //printf("compare %d with %d",first->floor_level_from,second->floor_level_from );
    bool same_buttonType = (first->button_type == second->button_type);
    bool same_floor = (first->floor_level == second->floor_level);
    return ( same_buttonType && same_floor) ? true : false;
}


Button_t* button_copyButton(Button_t* button){
    if(button){

        Button_t* p_button = malloc(sizeof(Button_t));
        p_button->button_type = button->button_type;
        p_button->floor_level = button->floor_level;
        return p_button;
    }
    return NULL;
}
