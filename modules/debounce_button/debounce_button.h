//=====[#include guards - begin]===============================================

#ifndef _DEBOUNCE_BUTTON_H_
#define _DEBOUNCE_BUTTON_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

/**
 * Represents the different states of 
 * a debounced button
 */
typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declarations (prototypes) of public functions]=========================

/**
 * Initializes the debounce button
 * @param pinName the name of the pin used to read the button 
 */
void debounceButtonInit(PinName pin);

/**
 * Update the dbounce button
 * @return the current state of the button
 */
buttonState_t debounceButtonUpdate();

//=====[#include guards - end]=================================================

#endif // _DEBOUNCE_BUTTON_H_