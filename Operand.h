#ifndef _OPERAND_H_
#define _OPERAND_H_
#include<stdio.h>

/* This header file contains the datastructure for storing
   properties associated with each operand of the instruction */

struct Oprnd {

    short int brkts; /* Is Operand can be enclosed in Brackets? 0 - inside Brackets, 1 - Both open and closed */
    short int enc_val; /* Value to add to baseval -- when operand is enclosed in brackets */
    short int open_val; /* Value to add to baseval -- when operand is not enclosed in brackets */

};

/* Function to initialise the operand -- called before initialiing the instruction */
struct Oprnd* init_operand(short int br, short int ev, short int ov);

#endif

