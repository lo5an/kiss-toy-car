/** 
 * Drive and avoid objects program for green model car 
 *
 */ 

#define TRUE 1
#define FALSE 0

#define SENSOR_PAUSE 500
// mseconds to wait for sensor update when looping

/*
 * Robot Behaviors (state based)
 */

#define WAKE  0 // POSTing
#define WAIT 2 // waiting for A button
#define START 5 // starting forward
#define FORWARD 10 // continuing forward 
#define VEER_LEFT 15 // veering left to avoid an object
#define VEER_RIGHT 20  // veering right to avoid an object
#define AVOID 25  // avoiding a collision
#define STOP 30  // stopping 


// Maximum number of times to loop through the AVOID state 
#define AVOID_MAX 3

/* 
 * Sensor, Servos, and Motors Configuration
 */


#define REAR_IR 0  
#define RIGHT_FRONT_IR 1
#define CENTER_FRONT_IR 2
#define LEFT_FRONT_IR 3

// IR reading indicatin collision
#define DETECT 75

// IR reading indicating object to left or right
#define DETECT_SIDE  75


/*
 * Steering Servo Config
 */

#define STEERING_SERVO 2
#define STEER_WAIT 0.5
//steering servo positions
#define STEER_RIGHT 1780
#define STEER_CENTER 1200+200
#define STEER_LEFT 620


/*
 * Drive Motor Config
 */

#define DRIVE_MOTOR 2
// drive motor speeds
#define FORWARD_SPD 750
#define STOP_SPD 0
#define REVERSE_SPD -750


#include "carlib.c"
