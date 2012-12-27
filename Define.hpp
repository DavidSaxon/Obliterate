/*************************************************\
| Defines overall fields and enums of the program |
\*************************************************/
#ifndef _DEFINE_H_
    #define _DEFINE_H_

//DEFINES
//the natural resolution of the window
#define NATURAL_RESO_X 1366
#define NATURAL_RESO_Y 768

#define PI 3.14159265

#define DEBRIS_WIDTH 10

#define MAX_SPEED 8

#define GRAVITY 0.1

//enumerator for the mode
enum {
	REFRESH = 0,
	STD,
	BLACKHOLE,
	BUTTERFLY,
	REFORM,
	SWISH
};

#endif