#include<stdio.h>
#include"Operand.h"
#include"Command.h"
#include<stdlib.h>
#include<string.h>
#include<search.h>


/*Converts the input string into upper case
  Required,since all the Instructions in the database are in Upper case */
void toupr(char* str) {

    while(*str != '\0') {
        if(islower(*str) != 0)
            *str = (*str)- 32;
        str++;
    }
}

/* Checks Whether the operand is enclosed inside the bracket
   Returns 0, if enclosed .. Else returns -1 */

int enclosed(char *str) {

    if(strlen(str) != 3)
        return -1;

    if(*str == '[' && str[2] == ']') {
        if(str[1] >= '0' && str[1] <= '9')
            return 0;
        else
            return -1;
    }
    else {
        return -1;
    }
}

/* Checks Whether the operand is not enclosed inside the bracket
   Returns 0, if not enclosed .. Else returns -1 */

int open(char* str) {

    if(strlen(str) != 1)
        return -1;

    if(*str >= '0' && *str <= '9')
        return 0;
    else
        return -1;
}

/*Process the instruction and returns the value of the instruction
  if not a valid instruction, returns -1;
  if not a supported instruction, returns -2
*/
int Process_ins(char** ins, int n) {

    int i =0;
    toupr(*(ins+i));
//                   printf("Command is : %s \n", *(ins+i));

    struct Command* cmd =  getCommand(*(ins+i)); /* Get the associated command */
//                   printEntry(*(ins+i));
    if(cmd == NULL)
        return -2;

    int en,on, bval;
    bval = cmd->baseval; /* initialise with the base value */

    if(n ==1)
        return bval;
    if( n-1 > cmd->No_of_Oprnds)
        return -1;

    struct Oprnd** op = (struct Oprnd**)cmd->Ops;
    /* Iterate over each of the operand and add the corresponding vlaue of
       the operand to the Instruction base value */
    for(i = 1; i< n; i++) {
        /* if Enclosed -- add the associated value to the base value */
        if((en = enclosed(*(ins+i)))==0) {
            //printf("Operand %d, adding %d \n", i,(*op)->enc_val);
            bval = bval + (*op)->enc_val;
        }

        /* if not enclosed and its valid, then add the associated value
           to the base value  else returns -1 -- The operand is not allowed to
            be given without parenthesis*/

        if ((on = open(*(ins+i)))==0) {
            if(((*op)->brkts > 0)) {
                // printf("Operand %d, adding %d \n", i,(*op)->open_val);
                bval = bval + (*op)->open_val;
            }
            else {
                bval = -1;
                return bval;
            }
        }
        op++;
    }
    //printf(" Computed value is : 0x%02x \n", bval);
    return bval;
}



