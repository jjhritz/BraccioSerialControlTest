#ifndef BRACCIOSERIAL_H
#define BRACCIOSERIAL_H

#include "BraccioExp.h"

int8_t cmd_sel_motor;   // servo selected by the serial command
int8_t cmd_inc_abs;     // determines if the movement is to be incremental (1) or absolute (0)
int16_t cmd_pos;         // the increment by which or position to which the servo will be moved

// Parses a serial command brought in from SerialExp
void parse_braccio_serial_command();

// prints a command parsed by parse_braccio_serial_command()
void print_parsed_braccio_command();

// passes the parsed command parameters to functions from BraccioExp
void pass_parsed_command(int8_t servo, int8_t inc_abs, int16_t move_dist);

#endif
