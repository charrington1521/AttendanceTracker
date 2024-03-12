//=====[#include guards - begin]===============================================

#ifndef _DATE_AND_TIME_H_
#define _DATE_AND_TIME_H_

#include <time.h>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * Gets the current real time
 * @return a struct containing real time info
 */
tm* dateAndTimeRead();

/**
 * Set the real time of the program
 * @param year 
 * @param month
 * @param day
 * @param hour
 * @param minute
 * @param second
 */
void dateAndTimeWrite( int year, int month, int day, 
                       int hour, int minute, int second );

//=====[#include guards - end]=================================================

#endif // _DATE_AND_TIME_H_