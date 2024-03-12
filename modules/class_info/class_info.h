//=====[#include guards - begin]===============================================

#ifndef _CLASS_INFO_H_
#define _CLASS_INFO_H_

//=====[Declaration of public defines]=========================================

/**
 *  The total number of students currently in the system
 */
#define NUM_STUDENTS                    5

//=====[Declaration of public data types]======================================

/**
 *A type which represents the different check in possibilities of a student.
 */
typedef enum
{
    EARLY,
    ON_TIME,
    LATE,
    ABSENT
} student_time_result_t;

/**
 *  A structure which includes the info associated with each student
 */
struct StudentInfo
{
    const char * name;
    student_time_result_t timeResult;
};

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @param code some string
 * @return true if there is a student associated with code
            false otherwise
 */
bool isCodeAStudent(char* code);

/**
 * Requires valid codes be passed to the method. 
 * Invalid student codes have undefined behavior. 
 * @param code code of the student to check in
 * @return the result of checking in the given student
 */
student_time_result_t checkInStudentByCode(char* code);

/**
 * Sets the class start time
 * Does not check for valid input
 * @param hour the hour start time 00-24
 * @param min  the minute start time 00-59
 */
void setClassStartTime(int hour, int min); //What should the input be?

/**
 * Get a students info by their index in a class info module
 * @param index int between 0 inclusive and NUM_STUDENTS exclusive
 * @return the info associated with student stored at given index
 */
StudentInfo * studentByIndex(int index);

/**
 * A method which initializes the class info
 */
void classInfoInit();

/**
 * A method which updates the class info
 */
void classInfoUpdate();

//=====[#include guards - end]=================================================

#endif // _CLASS_INFO_H_