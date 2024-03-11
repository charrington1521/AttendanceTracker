//=====[Libraries]=============================================================

//May be better to use the approach of matrix keypad where the led
 //component is initializes with the proper time increment. . .
#include "attendance_tracking_system.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "led.h"

//=====[Declaration of private defines]========================================

#define BLINK_LENGTH_MS         500

//=====[Declaration of private data types]=====================================

typedef enum
{
    FIRST,
    SECOND,
    THIRD,
    BASE,
} blink_state_t;   

//=====[Declaration and initialization of private global objects]===============

static PwmOut* red;
static PwmOut* green;
static PwmOut* blue;

static PwmOut* leds[] = {red, green, blue};

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static led_color_t current_color;
static blink_state_t cycle_pos;
static int accumulated_time = 0;

//=====[Declarations (prototypes) of private functions]========================

/**
 *  Set the color of the led using three of 0-255 RGB values
 */
static void setColor(int red, int green, int blue);

//=====[Implementations of public functions]===================================

void setColor(led_color_t color)
{
    current_color = color;
    switch(color)
    {
        case RED:
            setColor(255, 0, 0);
            break;
        case GREEN:
            setColor(0, 255, 0);
            break;
        case BLUE:
            setColor(0, 0, 255);
            break;
        default:
            setColor(0, 0, 0);
            break;
    }
}

/**
 *  Causes the led to blink two times with 500ms Up and Down times
 */
void blinkLed()
{
    cycle_pos = FIRST;
}

void ledInit(const PinName redPin, const PinName greenPin, const PinName bluePin)
{
    red = new PwmOut(redPin);
    green = new PwmOut(greenPin);
    blue = new PwmOut(bluePin);

    red->period(0.01f);
    green->period(0.01f);
    blue->period(0.01f);

    leds[RED]->write(0.0f);
    leds[GREEN]->write(0.0f);
    leds[BLUE]->write(0.0f);  

    current_color = NO_COLOR;
}

void ledUpdate()
{
    switch(cycle_pos)
    {
        case FIRST:
            setColor(current_color);
            if (accumulated_time >= BLINK_LENGTH_MS )
            {
                accumulated_time = 0;
                cycle_pos = SECOND;
            }
            else
            {
                accumulated_time += TIME_INCREMENT_MS;
            }
        break;

        case SECOND:
            setColor(NO_COLOR);
            if (accumulated_time >= BLINK_LENGTH_MS*2 )
            {
                accumulated_time = 0;
                cycle_pos = SECOND;
            }
            else
            {
                accumulated_time += TIME_INCREMENT_MS;
            }
        break;

        case THIRD:
            setColor(current_color);
            if (accumulated_time >= BLINK_LENGTH_MS*3 )
            {
                accumulated_time = 0;
                cycle_pos = SECOND;
            }
            else
            {
                accumulated_time += TIME_INCREMENT_MS;
            }
        break;

        default:
        break;
        
    }
}

//=====[Implementations of private functions]==================================

static void setColor(int red, int green, int blue)
{
    static const float ONE_OVER_255 = 0.0039215f; //Make Sure this works correctly
    leds[RED]->write(ONE_OVER_255 * red);
    leds[GREEN]->write(ONE_OVER_255 * green);
    leds[BLUE]->write(ONE_OVER_255 * blue);
}