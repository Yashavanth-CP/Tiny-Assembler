#include"Command.h"
#include<stdio.h>
#include<stdlib.h>

/* Function to initialise the commands - called by Database.c for initialising the available commands
   Arguements -- 1. bv --> base value of the instruction
                 2. n --> Number of Operands allowed.
                 3. opnds --> link to the Operands properties structure- could be NULL in case of instruction
                    without operands
   Return Value:  On success returns the pointer to the command structure, on Failure returns NULL.
*/
struct Command* Init_Command(int bv, int n, struct Oprnd** opnds) {

    struct Command* cmd = (struct Command*) malloc(sizeof(struct Command));
    if(cmd == NULL) {
        printf("Malloc failed in Init_Command() \n " );
        return NULL;
    }
    cmd->baseval = bv;
    cmd->No_of_Oprnds = n;
    cmd->Ops = opnds;

    struct Oprnd** Operands = (struct Oprnd**) opnds;
#if 0
    printf("Init_Command called :%d, %d \n", cmd->baseval, cmd->No_of_Oprnds);
    int i = 0;
    for(i =0; i < 1 ; i++) {
        printf("Operand %d brkts :%d \t",i, (*Operands)->brkts);
        printf("Operand %d enc_val: %d \t", i,(*Operands)->enc_val);
        printf("Operand %d open_val: %d \n", i, (*Operands)->open_val);
        Operands++;
    }
#endif
    return cmd;
};


/* As of now not being used  */
bool Validity(struct Command** cmd, int val, int index) {

    if(*cmd == NULL)
        return false;

    if(index >= (*cmd)->No_of_Oprnds)
        return false;

    if(val > ((*cmd)->Ops[index])->brkts)
        return false;

    return true;
}

/* As of now not being used */
short int GetValue(struct  Command** cmd, int enc, int index) {

    if( (*cmd) == NULL)
        return -1;

    if(index >= (*cmd)->No_of_Oprnds)
        return -1;

    if(enc == 0)
        return (*cmd)->Ops[index]->enc_val;

    if(enc == 1)
        return (*cmd)->Ops[index]->open_val;
};


