#include "BraccioSerial.h"

void parse_braccio_serial_command()
{
  char* strtokIndx;                           // used as an index by strtok()
  strtokIndx = strtok(tempChars, ",");        // get the motor number
  cmd_sel_motor = (int8_t) atoi(strtokIndx);  // convert to integer, then cast as 8-bit signed integer

  strtokIndx = strtok(NULL, ",");             // continue where the previous call left off to get the inc/abs command
  cmd_inc_abs = (int8_t) atoi(strtokIndx);    // convert to integer, then cast as 8-bit signed integer

  strtokIndx = strtok(NULL, ",");             // continue where the previous call left off to get the distance parametert
  cmd_pos = (int16_t) atoi(strtokIndx);       // convert to integer, then cast as 16-bit signed integer
}

void print_parsed_braccio_command()
{
    Serial.print("PARSED COMMAND::\t");
    Serial.print("Motor: ");  Serial.print(cmd_sel_motor);  Serial.print("\t");
    Serial.print("Increment Select: ");  Serial.print(cmd_inc_abs);  Serial.print("\t");
    Serial.print("Move Parameter: ");  Serial.print(cmd_pos);  Serial.print("\t");
    Serial.println();
    Serial.println();
}

void pass_parsed_command(int8_t servo, int8_t inc_abs, int16_t move_dist)
{
    switch(inc_abs)
    {
        case INCREMENTAL_MOVE:
            inc_servo_select(servo, move_dist);
            break;

        case ABSOLUTE_MOVE:
            abs_servo_select(servo, move_dist);
            break;

        default:
            // Serial.print("WARNING: ");  Serial.print(inc_abs);  Serial.println(" is not a valid selection!  Must be '0' or '1'!");
            break;
    }
}
