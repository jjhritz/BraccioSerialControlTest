#include "BraccioExp.h"


int16_t check_constraints(int8_t motor, int16_t pos)
{
    int16_t return_pos = pos;
    Serial.print("Validating position ");  Serial.print(pos);  Serial.print(" on motor ");  Serial.print(motor); 
    Serial.print("\t");
    
    // if the new position is less than the minimum constraint, return the minimum constraint
    if(pos < arm_constraints[motor][MINCONSTRAINT])
    {
        return_pos = arm_constraints[motor][MINCONSTRAINT];
        Serial.print("WARNING: exceeds MINIMUM constraint of: "); Serial.print(arm_constraints[motor][MINCONSTRAINT]);
        Serial.print("\t");
    }
    // else, if the new position is greater than the maximum constraint, return the maximum constraint
    else if(pos > arm_constraints[motor][MAXCONSTRAINT])
    {
        return_pos = arm_constraints[motor][MAXCONSTRAINT];
        Serial.print("WARNING: exceeds MAXIMUM constraint of: "); Serial.print(arm_constraints[motor][MAXCONSTRAINT]);
        Serial.print("\t");
    }
    else
    {
      Serial.print("Within constraints.\t");
    }

    Serial.print("Returning position: "); Serial.println(return_pos);
    Serial.println();
    return return_pos;
}

int16_t* move_arm_to(int16_t base_pos, int16_t shoul_pos, int16_t elbow_pos, int16_t elev_pos, int16_t rot_pos, int16_t grip_pos)
{
    // Set arm position array to new values
    // Ensure each new position does not exceed the motor's constraints
    arm_position[BASE_SERVO] = check_constraints(BASE_SERVO, base_pos);
    arm_position[SHOULDER_SERVO] = check_constraints(SHOULDER_SERVO, shoul_pos);
    arm_position[ELBOW_SERVO] = check_constraints(ELBOW_SERVO, elbow_pos);
    arm_position[ELEVATION_SERVO] = check_constraints(ELEVATION_SERVO, elev_pos);
    arm_position[ROTATION_SERVO] = check_constraints(ROTATION_SERVO, rot_pos);
    arm_position[GRIPPER_SERVO] = check_constraints(GRIPPER_SERVO, grip_pos);

    // Send new positions to Braccio controller
                      // (step delay, M0, M1, M2, M3, M4, M5);
    Braccio.ServoMovement(DEFAULTSTEPDELAY,  
                          arm_position[BASE_SERVO],
                          arm_position[SHOULDER_SERVO], 
                          arm_position[ELBOW_SERVO], 
                          arm_position[ELEVATION_SERVO], 
                          arm_position[ROTATION_SERVO], 
                          arm_position[GRIPPER_SERVO]);

    // return arm position array
    return arm_position;
}

int16_t* move_arm_by(int16_t base_inc, int16_t shoul_inc, int16_t elbow_inc, int16_t elev_inc, int16_t rot_inc, int16_t grip_inc)
{
    // Increment each arm position and send them to move_arm_to and return arm position array
    return move_arm_to( (arm_position[BASE_SERVO] + base_inc),
                        (arm_position[SHOULDER_SERVO] + shoul_inc),
                        (arm_position[ELBOW_SERVO] + elbow_inc),
                        (arm_position[ELEVATION_SERVO] + elev_inc),
                        (arm_position[ROTATION_SERVO] + rot_inc),
                        (arm_position[GRIPPER_SERVO] + grip_inc)
                        );
}

void print_arm_pos()
{
  Serial.print("ARM POSITION:: ");
  Serial.print("Base: "); Serial.print(arm_position[BASE_SERVO]); Serial.print("\t");
  Serial.print("Shoulder: "); Serial.print(arm_position[SHOULDER_SERVO]); Serial.print("\t");
  Serial.print("Elbow: "); Serial.print(arm_position[ELBOW_SERVO]); Serial.print("\t");
  Serial.print("Elevation: "); Serial.print(arm_position[ELEVATION_SERVO]); Serial.print("\t");
  Serial.print("Rotation: "); Serial.print(arm_position[ROTATION_SERVO]); Serial.print("\t");
  Serial.print("Gripper: "); Serial.print(arm_position[GRIPPER_SERVO]); Serial.print("\t");
  Serial.println();
  Serial.println();
}

void inc_servo_select(int8_t servo, int16_t move_dist)
{
    switch (servo)
    {
        case BASE_SERVO:
            move_arm_by(move_dist, 0, 0, 0, 0, 0);
            break;

        case SHOULDER_SERVO:
            move_arm_by(0, move_dist, 0, 0, 0, 0);
            break;

        case ELBOW_SERVO:
            move_arm_by(0, 0, move_dist, 0, 0, 0);
            break;

        case ELEVATION_SERVO:
            move_arm_by(0, 0, 0, move_dist, 0, 0);
            break;

        case ROTATION_SERVO:
            move_arm_by(0, 0, 0, 0, move_dist, 0);
            break;

        case GRIPPER_SERVO:
            move_arm_by(0, 0, 0, 0, 0, move_dist);
            break;

        default:
            // Serial.print("WARNING: ");  Serial.print(servo);  Serial.println(" is not a valid servo!  Must be in range [0,5]!");
            break;
    }
}

void abs_servo_select(int8_t servo, int16_t move_dist)
{
    switch (servo)
    {
        case BASE_SERVO:
            move_arm_to(move_dist, 
                        arm_position[SHOULDER_SERVO], 
                        arm_position[ELBOW_SERVO], 
                        arm_position[ELEVATION_SERVO], 
                        arm_position[ROTATION_SERVO], 
                        arm_position[GRIPPER_SERVO]
                        );
            break;

        case SHOULDER_SERVO:
            move_arm_to(arm_position[BASE_SERVO], 
                        move_dist, 
                        arm_position[ELBOW_SERVO], 
                        arm_position[ELEVATION_SERVO], 
                        arm_position[ROTATION_SERVO], 
                        arm_position[GRIPPER_SERVO]
                        );
            break;

        case ELBOW_SERVO:
            move_arm_to(arm_position[BASE_SERVO], 
                        arm_position[SHOULDER_SERVO], 
                        move_dist, 
                        arm_position[ELEVATION_SERVO], 
                        arm_position[ROTATION_SERVO], 
                        arm_position[GRIPPER_SERVO]
                        );
            break;

        case ELEVATION_SERVO:
            move_arm_to(arm_position[BASE_SERVO], 
                        arm_position[SHOULDER_SERVO], 
                        arm_position[ELBOW_SERVO], 
                        move_dist, 
                        arm_position[ROTATION_SERVO], 
                        arm_position[GRIPPER_SERVO]
                        );
            break;

        case ROTATION_SERVO:
            move_arm_to(arm_position[BASE_SERVO], 
                        arm_position[SHOULDER_SERVO], 
                        arm_position[ELBOW_SERVO], 
                        arm_position[ELEVATION_SERVO], 
                        move_dist, 
                        arm_position[GRIPPER_SERVO]
                        );
            break;

        case GRIPPER_SERVO:
            move_arm_to(arm_position[BASE_SERVO], 
                        arm_position[SHOULDER_SERVO], 
                        arm_position[ELBOW_SERVO], 
                        arm_position[ELEVATION_SERVO], 
                        arm_position[ROTATION_SERVO], 
                        move_dist
                        );
            break;
            
        default:
            // Serial.print("WARNING: ");  Serial.print(servo);  Serial.println(" is not a valid servo!  Must be in range [0,5]!");
            break;
    }
}
