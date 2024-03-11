#include "mbed.h"
#include "attendance_tracking_system.h"

// main() runs in its own thread in the OS
int main()
{
    attendanceTrackingInit();
    while (true) {
        attendanceTrackingUpdate();
    }
}

