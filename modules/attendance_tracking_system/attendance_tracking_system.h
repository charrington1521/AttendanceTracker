//=====[#include guards - begin]===============================================

#ifndef _ATTENDANCE_TRACKING_H_
#define _ATTENDANCE_TRACKING_H_

#include "lcd.h"

//=====[Declaration of public defines]=========================================

/**
 * The delay used within the attendance tracking system
 */
#define TIME_INCREMENT_MS                                   10

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * Initializes the attendance tracking system
 */
void attendanceTrackingInit();

/**
 * Updates the attendance tracking system
 */
void attendanceTrackingUpdate();

//=====[#include guards - end]=================================================

#endif // _ATTENDANCE_TRACKING_H_