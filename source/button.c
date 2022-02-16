/**
 * @file
 * @brief Implementation file for queue file
 */


#include "button.h"
//#include <stdlib.h>



bool button_equalButtons(Button_t* first, Button_t* second){
    //debug
    //printf("compare %d with %d",first->floor_level_from,second->floor_level_from );
    bool same_buttonType = (first->button_type == second->button_type);
    bool same_floor = (first->floor_level_from == second->floor_level_from);
    return ( same_buttonType && same_floor) ? true : false;
}