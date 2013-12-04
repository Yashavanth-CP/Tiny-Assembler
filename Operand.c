#include"Operand.h"
#include<stdlib.h>

/* Initialise the operand -- called from Database.c while initilising
   all the available commands
*/
struct Oprnd* init_operand(short int brs, short int ev, short int ov) {

    struct Oprnd* toRet = (struct Oprnd*)malloc(sizeof(struct Oprnd));
    if(toRet == NULL) {
        printf("Malloc failed \n");
        return NULL;
    }

    toRet->brkts = brs;
    toRet->enc_val = ev;
    toRet->open_val = ov;
    return toRet;
};


