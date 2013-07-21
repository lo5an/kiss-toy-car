/*
 *  Function Prototypes
 */


void wake();

void drive_forward();
void drive_reverse();
void drive_stop();


void steer( int pos );
void steer_center();
void steer_right();
void steer_left();

int detect_side(int sensor);
int detect_straight(int sensor);



int main()
{
    int mpos_count = 0; // counter to stop if blocked
        
    int avoid_count = 0; // counter to prevent AVOID loops
        
    // Intialize sensors, motors, servos, etc
    int state = WAKE;
    wake();
        
    // set to first driving state and get ready
    state = WAIT; 
        
    while (!b_button()){  // run until halted with B button
                
   
                         
        // get motor position for stall test
        // if motor position goes down, the motor is stalled and we need to stop 
        // but this approach doesn't seem to be working
        clear_motor_position_counter(DRIVE_MOTOR);
        mpos_count=get_motor_position_counter(DRIVE_MOTOR);

        if (WAIT == state) {            
           // wait until the A button is pressed

            printf("Waiting for A button to go. \n");
            while (!a_button()){    
                msleep(SENSOR_PAUSE);
            }
                        
            printf("Press B button to stop. \n");       
                        
            state = START;
                        
        }
        else if (START == state) {
                
            avoid_count=0; // since we made it to start, we're not in an avoid loop
      
            // start driving forward
            steer_center();
            drive_forward();
                
            state = FORWARD;
                        
        } else if (FORWARD == state){
                                                
            // drive forward until an obstacle is detected
            // no speed change, but make sure we're going straight ahead
            steer_center(); 
                                                
            if  (detect_straight(CENTER_FRONT_IR)) { state = AVOID;} // if we're about to hit something
            else if (mpos_count >= get_motor_position_counter(DRIVE_MOTOR)) { state=STOP;} // stop if the motor stalls
            else if (detect_side(RIGHT_FRONT_IR) && detect_side(LEFT_FRONT_IR) ){ state = AVOID; }
            else if (detect_side(RIGHT_FRONT_IR)){ state = VEER_LEFT;} // if we need to dodge left
            else if (detect_side(LEFT_FRONT_IR)){ state = VEER_RIGHT;} // if we need to dodge right
            else { state = FORWARD;}
                        
        } else if (VEER_RIGHT == state) {
                        
            // steer to the right, but don't slow down
            steer_right();
                        
            if  (detect_straight(CENTER_FRONT_IR)) { state = AVOID;} // if we're about to hit something
            else if (mpos_count >= get_motor_position_counter(DRIVE_MOTOR)) { state=STOP;} // stop if the motor stalls
            else if (detect_side(RIGHT_FRONT_IR) && detect_side(LEFT_FRONT_IR) ){ state = AVOID; }
            else if (detect_side(RIGHT_FRONT_IR)){ state = VEER_LEFT;} // if we need to dodge left
            else if (detect_side(LEFT_FRONT_IR)) { state = VEER_RIGHT;} // if we need to dodge right
            else { state = FORWARD ;}
                        
        } else if (VEER_LEFT == state) {
                        
            // steer to the left, but don't slow down
            steer_left();
                        
            if (detect_straight(CENTER_FRONT_IR)) { state = AVOID;} // if we're about to hit something
            else if (mpos_count >= get_motor_position_counter(DRIVE_MOTOR)) { state=STOP;} // stop if the motor stalls
            else if (detect_side(RIGHT_FRONT_IR) && detect_side(LEFT_FRONT_IR) ){ state = AVOID; }
            else if (detect_side(RIGHT_FRONT_IR)){ state = VEER_LEFT;} // if we need to dodge left
            else if (detect_side(LEFT_FRONT_IR)) { state = VEER_RIGHT;} // if we need to dodge right
            else { state = FORWARD ;}
                                                
        } else if (AVOID == state) {
                        
            // keep track of how many avoids
            //avoid_count++; 
			avoid_count=0; // avoid keeping track of avoids
                        
            // something is in front of us, we need to try a different direction
            drive_stop();
                        
            // steer left or right at random
            // we're backing up, so direction of travel will be swapped
            if ((rand()%2)){ steer_right();}
            else{ steer_left();}

            drive_reverse();// backup to clear the obstacle
            if (! detect_straight(REAR_IR)){ sleep(1); } 
            if (! detect_straight(REAR_IR)){ sleep(1); } 
                        
            drive_stop();
                        
            if (avoid_count > AVOID_MAX) { state=STOP;} // stay out of avoid loops
            else if (detect_straight(CENTER_FRONT_IR) ) { state = AVOID; } //if we're about to hit something             
            else if (detect_side(RIGHT_FRONT_IR) && detect_side(LEFT_FRONT_IR) ){ state = AVOID; }
            else { state = START ;} 
                        
        } else if (STOP == state ) {
                        
            // something is up, lets stop
                        
            drive_stop();
	        steer_center();
                        
            state = WAIT;
                        
        } // end of behavior state machine
                        
    } // end of B button loop
                        
}
                        
                        
                        
/*
 * Initialize robot sensors, motors, etc
 */
void wake() {
    //set ports to floating for ET Sensors and pause to let it happen
    set_each_analog_state(1,1,1,1,0,0,0,0);
    sleep(1);
    enable_servos();
}
                        
                        
/*
 * Basic Driving: forward, reverse, and stop
 */
                        
void drive_forward(){ mav(DRIVE_MOTOR, FORWARD_SPD);}
void drive_reverse(){ mav(DRIVE_MOTOR, REVERSE_SPD);}
void drive_stop(){ mav(DRIVE_MOTOR, STOP_SPD);}
                        
                        
/* 
 * Sets the steering servo to the desired position to turn
 */ 
                        
void steer( int pos ) {
    set_servo_position (STEERING_SERVO, pos);
}
                        
/* 
 * steering convenience functions
 */
                        
void steer_center() { steer(STEER_CENTER);}
void steer_right() { steer(STEER_RIGHT);}
void steer_left() { steer(STEER_LEFT);}
                        
                        
/*
 * Detect an object straight ahead
 */
                        
int detect_straight(int sensor){
    int result=-1;
                        
    if (analog(sensor) > DETECT){ result=TRUE;}
    else { result = FALSE;}
    return result;
}
                        
                        
/*
 * Detect an object to the left or right
 */
                        
int detect_side(int sensor){
    int result=-1;
    if (analog(sensor) > DETECT_SIDE){ result=TRUE;}
    else { result = FALSE;}
    return result;
}
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                        
                
