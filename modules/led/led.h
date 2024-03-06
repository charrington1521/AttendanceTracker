//=====[#include guards - begin]===============================================

#ifndef _LED_H_
#define _LED_H_

//=====[Declaration of public defines]=========================================

#include "mbed.h"

//=====[Declaration of public data types]======================================

typedef enum
{
    RED,
    GREEN,
    BLUE,
    NO_COLOR
} led_color_t;

//=====[Declarations (prototypes) of public functions]=========================

void setColor(led_color_t color);

/**
 *  Causes the led to blink two times with 500ms Up and Down times
 */
void blinkLed();

/**
 *  Initializes a RGB led with the given list of pin names
 * The PinName list is expected in the following format:
 *  PWM pin Red, PWM pin Green, PWM pin Blue
 */
void ledInit(const PinName redPin, const PinName greenPin, const PinName bluePin);

void ledUpdate();

//=====[#include guards - end]=================================================

#endif // _LED_H_