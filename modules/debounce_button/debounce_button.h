//=====[#include guards - begin]===============================================

#ifndef _DEBOUNCE_BUTTON_H_
#define _DEBOUNCE_BUTTON_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declarations (prototypes) of public functions]=========================

void debounceButtonInit(PinName pin);

buttonState_t debounceButtonUpdate();

//=====[#include guards - end]=================================================

#endif // _DEBOUNCE_BUTTON_H_