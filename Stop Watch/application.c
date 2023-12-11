/* 
 * File:   application.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 */

#include "application.h"

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

button_t btn1 = {
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN0,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn2 = {
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN1,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

button_t btn3 = {
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

segment_t segment1 = {
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN0,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[0].logic = GPIO_LOW,
    
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN1,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].logic = GPIO_LOW,
    
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN2,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].logic = GPIO_LOW,
    
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN3,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].logic = GPIO_LOW,
    
    .segment_type = SEGMENT_COMMON_CATHODE
};

segment_t segment2 = {
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN4,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[0].logic = GPIO_LOW,
    
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN5,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].logic = GPIO_LOW,
    
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN6,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].logic = GPIO_LOW,
    
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN7,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].logic = GPIO_LOW,
    
    .segment_type = SEGMENT_COMMON_CATHODE
};

void counter(uint8 seconds);
void application_intialize(void);

button_state_t resetbtn_read = BUTTON_RELEASED;
button_state_t rbtn_read  = BUTTON_RELEASED;
button_state_t pbtn_read  = BUTTON_RELEASED;

uint8 temp = 0;
uint8 zero = 0;

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
    application_intialize();
    
    ret = led_initialize(&led1);
    
    ret = seven_segement_intialize(&segment1);
    ret = seven_segement_intialize(&segment2);
    
    for(uint8 counter = 0 ; counter <= 99; counter++){
        
        ret = button_read_state(&btn1, &resetbtn_read);
        ret = button_read_state(&btn2, &rbtn_read);
        ret = button_read_state(&btn3, &pbtn_read);
        
        
        ret = seven_segement_write_number((&segment1), ( (uint8)(counter%10) ) );     
        ret = seven_segement_write_number((&segment2), ( (uint8)(counter/10) ) );
        
        if(BUTTON_PRESSED == resetbtn_read){
            counter = -1;
        }
        
        else if(BUTTON_PRESSED == pbtn_read){
            while(rbtn_read  = BUTTON_RELEASED){
                ret = button_read_state(&btn2, &rbtn_read);
                if(BUTTON_PRESSED == rbtn_read){
                    break;
                }
            }
        }
        
        
        __delay_ms(1000);
    }

//    while(1){
//        
//        
//        if(BUTTON_PRESSED == resetbtn_read){
//            counter(zero);
//        }
//            
//        
//        if(BUTTON_PRESSED == rbtn_read){
//            
//        }
//        else{
//            
//        }
//        
//        if(BUTTON_PRESSED == pbtn_read){
//            
//        }
//        else{
//            
//        }
//    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}

//void counter(uint8 seconds){
//    __delay_ms(100);
//    resetbtn_read = BUTTON_RELEASED;
//    rbtn_read  = BUTTON_RELEASED;
//    pbtn_read  = BUTTON_RELEASED;
//    
//    Std_ReturnType ret = E_NOT_OK; 
//        for(uint8 counter = 0 ; counter <= 99; counter++){
//        ret = seven_segement_write_number((&segment1), ( (uint8)(counter%10) ) );     
//        ret = seven_segement_write_number((&segment2), ( (uint8)(counter/10) ) );
//        __delay_ms(1000);
//    
//} 
//}
