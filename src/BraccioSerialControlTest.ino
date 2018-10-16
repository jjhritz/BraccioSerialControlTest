#include "SerialExp.h"
#include "BraccioExp.h"
#include "BraccioSerial.h"


const int8_t numChars = 8;              // Maximum size of a command message; start- and end-of-message characters are not stored.
char commandMessage[numChars];          // stores the received command for external access

long finish_command_timestamp = 0;
long current_timestamp;

void test_move_arm_to()
{
    delay(2000);
    // Move arm to vertical position
    move_arm_to(90, 90, 90, 90, 90, 73);
    print_arm_pos();
    
    delay(2000);
    // Move arm to safety position
    move_arm_to(90, 45, 180, 180, 90, 10);
    print_arm_pos();

    delay(2000);
    // Move arm to vertical position
    move_arm_to(90, 90, 90, 90, 90, 73);
    print_arm_pos();

    delay(1000);
    // Try to violate shoulder maximum constraint
    // 180 is greater than the shoulder's maximum constraint of 165
    move_arm_to(90, 180, 90, 90, 90, 73);
    print_arm_pos();

    delay(1000);
    // Try to violate shoulder minimum constraint
    // 0 is less than the shoulder's minimum constraint of 15
    move_arm_to(90, 0, 90, 90, 90, 73);
    print_arm_pos();

     delay(1000);
    // Try to violate gripper minimum constraint
    // 0 is less than the gripper's minimum constraint of 10
    move_arm_to(90, 90, 90, 90, 90, 0);
    print_arm_pos();

    delay(1000);
    // Try to violate gripper maximum constraint
    // 80 is less than the gripper's maximum constraint of 73
    move_arm_to(90, 90, 90, 90, 90, 80);
    print_arm_pos();

     delay(2000);
    // Move arm to vertical position
    move_arm_to(90, 90, 90, 90, 90, 73);
    print_arm_pos();
}

void test_move_arm_by()
{
    delay(2000);
    // Move arm to vertical position
    move_arm_to(90, 90, 90, 90, 90, 73);
    print_arm_pos();

    delay(2000);
    // rotate the base 30 degrees right, then rotate 60 degrees back, then recenter
    move_arm_by(30, 0, 0, 0, 0, 0);
    print_arm_pos();
    move_arm_by(-60, 0, 0, 0, 0, 0);
    print_arm_pos();
    move_arm_by(30, 0, 0, 0, 0, 0);
    print_arm_pos();

    delay(2000);
    // rotate the shoulder 20 degrees forward, then then 40 degrees back, then recenter
    move_arm_by(0, 20, 0, 0, 0, 0);
    print_arm_pos();
    move_arm_by(0, -40, 0, 0, 0, 0);
    print_arm_pos();
    move_arm_by(0, 20, 0, 0, 0, 0);
    print_arm_pos();

    delay(2000);
    // rotate the elbow 30 degrees forward, then then 60 degrees back, then recenter
    move_arm_by(0, 0, 30, 0, 0, 0);
    print_arm_pos();
    move_arm_by(0, 0, -60, 0, 0, 0);
    print_arm_pos();
    move_arm_by(0, 0, 30, 0, 0, 0);
    print_arm_pos();

    delay(2000);
    // elevate the wrist 30 degrees up, then then 60 degrees down, then recenter
    move_arm_by(0, 0, 0, 30, 0, 0);
    print_arm_pos();
    move_arm_by(0, 0, 0, -60, 0, 0);
    print_arm_pos();
    move_arm_by(0, 0, 0, 30, 0, 0);
    print_arm_pos();

    delay(2000);
    // rotate the wrist 30 degrees right, then then 60 degrees left, then recenter
    move_arm_by(0, 0, 0, 0, 30, 0);
    print_arm_pos();
    move_arm_by(0, 0, 0, 0, -60, 0);
    print_arm_pos();
    move_arm_by(0, 0, 0, 0, 30, 0);
    print_arm_pos();

    delay(2000);
    // Close the grabber by 20 degrees, then reopen
    move_arm_by(0, 0, 0, 0, 0, 20);
    print_arm_pos();
    move_arm_by(0, 0, 0, 0, 0, -20);
    print_arm_pos();
    
}

void reset_ending_timestamp()
{
    finish_command_timestamp = millis() + 500;
}

void setup()
{
    Serial.begin(9600);
    
    Braccio.begin();
    // Move arm to default safety position
    Braccio.ServoMovement(DEFAULTSTEPDELAY,  
                          arm_position[BASE_SERVO],
                          arm_position[SHOULDER_SERVO], 
                          arm_position[ELBOW_SERVO], 
                          arm_position[ELEVATION_SERVO], 
                          arm_position[ROTATION_SERVO], 
                          arm_position[GRIPPER_SERVO]);

    finish_command_timestamp = millis();
    current_timestamp = millis();
    
    /*
    print_arm_pos();
    Serial.println("Setup COMPLETE ");
    Serial.println();

    Serial.println("This demo expects 3 integers: a servo number, a 1 or 0, and the number of degrees to move it");
    Serial.println("For the second integer, 1 means the 3rd integer is an incremental movement.");
    Serial.println("0 means the 3rd integer is an absolute movement.");
    Serial.println("Enter data in this style <1,1,5>");
    Serial.println("The constraints on each servo are as follows:");
    Serial.println("0 (Base): 0 (left) to 180 (right) degrees");
    Serial.println("1 (Shoulder): 15 (back) to 165 (forward) degrees");
    Serial.println("2 (Elbow): 0 to 180 degrees");
    Serial.println("3 (Wrist elevation): 0 to 180 degrees");
    Serial.println("4 (Wrist rotation): 0 to 180 degrees");
    Serial.println("5 (Grabber): 10 to 73 degrees.  10 is open, 73 is closed.");
    Serial.println("The motors WILL NOT be permitted to advance beyond these constraints.");
    Serial.println();
    */
}

void loop()
{
    current_timestamp = millis();

    if(current_timestamp > finish_command_timestamp)
    {
        move_arm_to(arm_position[BASE_SERVO],
                    arm_position[SHOULDER_SERVO], 
                    arm_position[ELBOW_SERVO], 
                    arm_position[ELEVATION_SERVO], 
                    arm_position[ROTATION_SERVO], 
                    arm_position[GRIPPER_SERVO]);
    }
    
    allocateStrings(numChars, commandMessage);       // allocates space for received message arrays
    recvWithStartEndMarkers(numChars, '<', '>');     // receives message

    if (newData == true)
    {
        strcpy(tempChars, receivedChars);   // copy received string to protect original data

        parse_braccio_serial_command();
        // print_parsed_braccio_command();
      
        newData = false;                    // Tell the system we have parsed the data and are ready for a new command.
      
        pass_parsed_command(cmd_sel_motor,  // move the arm
                          cmd_inc_abs, 
                          cmd_pos);
        reset_ending_timestamp();            
    }

    // test_move_arm_to();

    // test_move_arm_by();
}
