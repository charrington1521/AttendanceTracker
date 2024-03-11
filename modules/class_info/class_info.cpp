//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "lcd.h"
#include "class_info.h"
#include "date_and_time.h"
#include <time.h>

//=====[Declaration of private defines]========================================

const char* STUDENT_CODES[NUM_STUDENTS] = {"123ABC", "ABCDAB"};

//=====[Declaration of private data types]=====================================

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
static int classStartTime[2] = {8, 10};

static StudentInfo* studentInfo[NUM_STUDENTS];

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
    return studentByIndex(indexOfStudentByCode(code))->timeResult == ON_TIME;
}

void checkInStudentByCode(char* code)
{
    tm* currentTime = dateAndTimeRead();
    student_time_result_t check_in_result;
    char str[2];
    sprintf(str, "%d", currentTime->tm_hour%24);
    lcdStringWrite(str);
    if (currentTime->tm_hour%24 < classStartTime[HOUR]) 
    {
        check_in_result = LATE;
    }
    else if (currentTime->tm_hour%24 > classStartTime[HOUR])
    {
        check_in_result = EARLY;
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

    studentByIndex(indexOfStudentByCode(code))->timeResult = check_in_result;
}

/**
 *  What should this take as input?
 */
void setClassStartTime(int hour, int min)
{
    classStartTime[0] = hour;
    classStartTime[1] = min;
}

StudentInfo * studentByIndex(int index)
{
    return studentInfo[index];
}

void classInfoInit()
{
    //Possibly implement a pull of stored info from flash mem. . .
    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        studentInfo[i] = new StudentInfo;
        studentInfo[i]->timeResult = ABSENT;
    }
    studentInfo[0]->name = "Amy";
    studentInfo[1]->name = "Bob";
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

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        if (strcmp(code, STUDENT_CODES[i]) == 0)
        {
            toReturn = i;
        }
    }

    return toReturn;
}