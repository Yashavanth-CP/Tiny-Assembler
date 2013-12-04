#ifndef _COMMAND_H_
#define _COMMAND_H_
#include<stdio.h>
#include<stdbool.h>
#include"Operand.h"

/*This file is an interface for the command datastructure
  Each Command holds information-
       1. Base value of the instruction
       2. Number of Operands it can take
       3. It contains the properties of each operand
*/

struct Command {
    int baseval; /* Base value for calculating the code */
    int No_of_Oprnds; /* Maximum number of operands allowed */
    struct Oprnd** Ops; /* Link to the preoperties of each operand */
};

/* Interface functions */
struct Command* Init_Command(int bv, int n, struct Oprnd** oprnds);
bool Validity(struct Command** cmd, int val, int index);
short int GetValue(struct  Command** cmd, int enc, int index);

#endif


