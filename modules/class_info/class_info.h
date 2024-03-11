//=====[#include guards - begin]===============================================

#ifndef _CLASS_INFO_H_
#define _CLASS_INFO_H_

//=====[Declaration of public defines]=========================================

#define NUM_STUDENTS                    2

//=====[Declaration of public data types]======================================

typedef enum
{
    EARLY,
    ON_TIME,
    LATE,
    ABSENT
} student_time_result_t;

struct StudentInfo
{
    const char * name;
    student_time_result_t timeResult;
};

//=====[Declarations (prototypes) of public functions]=========================

bool isCodeAStudent(char* code);

bool isStudentOnTime(char* code);

void checkInStudentByCode(char* code);

void setClassStartTime(int hour, int min); //What should the input be?

StudentInfo * studentByIndex(int index);

void classInfoInit();

void classInfoUpdate();

//=====[#include guards - end]=================================================

#endif // _CLASS_INFO_H_