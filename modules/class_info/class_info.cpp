//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "class_info.h"
#include "date_and_time.h"
#include <time.h>

//=====[Declaration of private defines]========================================

#define NUM_STUDENT_CODES                    1

const char* STUDENT_CODES[NUM_STUDENT_CODES] = {"123abc"};

//=====[Declaration of private data types]=====================================

typedef enum
{
    EARLY,
    ON_TIME,
    LATE
} student_time_result_t;

typedef enum
{
    HOUR,
    MINUTE
} class_start_time_indices_t;

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

/**
 * When the class starts
 *  [0] Hour, [1] minute
 */
static int classStartTime[2];

static student_time_result_t student_time_results[NUM_STUDENT_CODES];

//=====[Declarations (prototypes) of private functions]========================

static int indexOfStudentByCode(char* code);

//=====[Implementations of public functions]===================================

bool isCodeAStudent(char* code)
{
    return indexOfStudentByCode(code) >= 0;
}

/**
 * Would we prefer to send back a student_time_result?
 */
bool isStudentOnTime(char* code)
{
    return student_time_results[indexOfStudentByCode(code)] == ON_TIME;
}

void checkInStudentByCode(char* code)
{
    tm* currentTime = dateAndTimeRead();
    student_time_result_t check_in_result;
    if (currentTime->tm_hour < classStartTime[HOUR]) 
    {
        check_in_result = EARLY;
    }
    else if (currentTime->tm_hour > classStartTime[HOUR])
    {
        check_in_result = LATE;
    }
    else
    {
        if (currentTime->tm_min < classStartTime[MINUTE])
        {
            check_in_result = EARLY;
        }
        else if (currentTime->tm_min > classStartTime[MINUTE])
        {
            check_in_result = LATE;
        }   
        else
        {
            check_in_result = ON_TIME;
        }
    }

    student_time_results[indexOfStudentByCode(code)] = check_in_result;
}

/**
 *  What should this take as input?
 */
void setClassStartTime()
{

}

void classInfoInit()
{
    //Possibly implement a pull of stored info from flash mem. . .
}

void classInfoUpdate()
{
    //Is this needed?
}

//=====[Implementations of private functions]==================================

/**
 *  Returns the index of the student with the given code
 *      -1 if no such student
 */
static int indexOfStudentByCode(char* code)
{
    int toReturn = -1;

    for (int i = 0; i < NUM_STUDENT_CODES; i++)
    {
        if (strcmp(code, STUDENT_CODES[i]) == 0)
        {
            toReturn = i;
        }
    }

    return toReturn;
}