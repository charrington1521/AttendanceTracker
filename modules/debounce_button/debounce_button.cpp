//=====[Libraries]=============================================================

#include "attendance_tracking_system.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "debounce_button.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_BUTTON_TIME_MS         40

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of private global objects]===============

DigitalIn* button;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int accumulatedDebounceButtonTime     = 0;
buttonState_t buttonState;

//=====[Declarations (prototypes) of private functions]========================

void debounceButtonInit();

//=====[Implementations of public functions]===================================

void debounceButtonInit(PinName pin)
{
    button = new DigitalIn(pin);
    button->mode(PullDown); //Should this be pullDown?
    debounceButtonInit();
}

void debounceButtonInit()
{
    if( *button == 1) {
        buttonState = BUTTON_UP;
    } else {
        buttonState = BUTTON_DOWN;
    }
}

buttonState_t debounceButtonUpdate()
{
    switch( buttonState ) {

    case BUTTON_UP:
        if( *button ) {
            buttonState = BUTTON_FALLING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_FALLING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( *button ) {
                buttonState = BUTTON_DOWN;
            } else {
                buttonState = BUTTON_UP;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !*button ) {
            buttonState = BUTTON_RISING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_RISING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( !*button ) {
                buttonState = BUTTON_UP;
            } else {
                buttonState = BUTTON_DOWN;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    default:
        debounceButtonInit();
        break;
    }
    return buttonState;
}

//=====[Implementations of private functions]==================================
