# HexClock
 Fork of HexClock codebase

 Code based on the project posted at:
 https://www.instructables.com/id/RGB-HexMatrix-IOT-Clock/
 
 Updated code to add modes to turn the LEDs off at night (tested) and to turn off LEDs off on the weekend (untested).
 
#define NIGHT_MODE        1     //Set night mode where 0 is off and 1 is on (Night mode turns the clock off at night)
#define WEEKEND_MODE      0     //Set weekend mode where 0 is off and 1 is on (Weekend mode turns the clock off on the weekends)
#define NIGHT_OFF_TIME    22    //Time (hour) that clock turns off when night mode is active
#define NIGHT_ON_TIME     7     //Time (hour) that clock turns on when night mode is active

Updated code to show minutes 1 through 9 as two-digits instead of one digit (e.g., 2 is shown as 02)