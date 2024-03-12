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

/**
 * Changes the color of the led
 * @param color the color to set the led to
 */
void setColor(led_color_t color);

/**
 * Causes the led to blink two times 
 */
void blinkLed();

/**
 * Initializes a tri color led given 3 pins
 * @param redPin
 * @param greenPin
 * @param bluePin
 */
void ledInit(const PinName redPin, const PinName greenPin, const PinName bluePin);

/**
 * Updates the led
 */
void ledUpdate();

//=====[#include guards - end]=================================================

#endif // _LED_H_