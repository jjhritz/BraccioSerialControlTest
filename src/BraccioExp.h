#ifndef BRACCIOEXP_H
#define BRACCIOEXP_H

#include <Braccio.h>
#include <Servo.h>

#define DEFAULTSTEPDELAY 20     // step delay for the Braccio arm's servos, in ms.

#define MINCONSTRAINT 0
#define MAXCONSTRAINT 1

#define BASE_SERVO 0
#define SHOULDER_SERVO 1
#define ELBOW_SERVO 2
#define ELEVATION_SERVO 3
#define ROTATION_SERVO 4
#define GRIPPER_SERVO 5

#define ABSOLUTE_MOVE  0
#define INCREMENTAL_MOVE 1

Servo base;           // M0   
Servo shoulder;       // M1
Servo elbow;          // M2
Servo wrist_ver;      // M3
Servo wrist_rot;      // M4
Servo gripper;        // M5

// Current positions of the arm servos.  Defaults to safety position
                        //M0, M1, M2,  M3,  M4, M5
int16_t arm_position[] = {90, 45, 180, 180, 90, 10};

// Positional constraints on the servos, in degrees, in the form M0[min, max], M1[min,max], etc.
const int16_t arm_constraints[6][2] = { {1, 179},   // M0 Base                  default: {0, 180}
                                        {17, 163},  // M1 Shoulder              default: {15, 165}
                                        {1, 179},   // M2 Elbow                 default: {0, 180}
                                        {1, 179},   // M3 Wrist elevation       default: {0, 180}
                                        {1, 179},   // M4 Wrist rotation        default: {0, 180}
                                        {11, 72},   // M5 Grabber (Open, Close) default: {10, 73}
};

// Checks and rectifies servo constraint violations.  
// Returns provided position if valid, otherwise returns maximum or minimum constraint, depending on which was violated
int16_t check_constraints(int8_t motor, int16_t pos);

// Moves arm to an absolute position based on the provided values.  Returns new arm position.
int16_t* move_arm_to(int16_t base_pos, int16_t shoul_pos, int16_t elbow_pos, int16_t elev_pos, int16_t rot_pos, int16_t grip_pos);

// Increments arm position by the provided values.  Returns new arm position.
int16_t* move_arm_by(int16_t base_inc, int16_t shoul_inc, int16_t elbow_inc, int16_t elev_inc, int16_t rot_inc, int16_t grip_inc);

// Prints the current values of arm_position to the serial port
void print_arm_pos();

// Wrapper for switch case to select which servo is being moved incrementally
void inc_servo_select(int8_t servo, int16_t move_dist);

// Wrapper for switch case to select which servo is being moved absolutely
void abs_servo_select(int8_t servo, int16_t move_dist);

#endif
