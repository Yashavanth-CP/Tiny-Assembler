#define _GNU_SOURCE
#include<search.h>
#include"Operand.h"
#include"Command.h"
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<search.h>

/* The Database contains all the supported commands and their Properties
   in a HASH table lookup.
   Used the HASH table avalibale in glibc using hcreate()
   Disadvantage:  only one hash table can be used anytime
*/

/* Not being used */
char* getKey(char* k) {

    char* key = (char*) malloc(sizeof(char)*strlen(k));
    if(key == NULL) {
        printf("Memory allocation for AND falied \n");
        return NULL;
    }
    strcpy(key, k);
    return key;
}

/* Get the command information by looking into the HashTable
   Input : char* key --  in upper case only. Lower case keys fail.
   return: On Success -- returns the Command structure
           On Failure -- returns NULL
*/
struct Command* getCommand(char* key) {

    if(key == NULL) {
        printf("Key is NULL \n");
        return NULL;
    }

    ENTRY* found;
    ENTRY item;
    item.key = key;
    if((found = hsearch(item, FIND)) != NULL) {
        struct Command* toRet  = (struct Command*)(found->data);
        return toRet;
    }

    return NULL;
}

/* Prints the information of the command by looking up from the HASH Table
    Output -- prints the command information and returns nothing */
void printEntry(char* key) {

    if(key == NULL) {
        printf("Key is NULL \n");
        return;
    }

    ENTRY* found;
    ENTRY item;
    item.key = key;
    if((found = hsearch(item, FIND)) != NULL) {
        struct Command* it  = (struct Command*)(found->data);
        struct Oprnd** Operands = (struct Oprnd**) it->Ops;
        printf("Details of command are: \n");
        printf("  Command Name: %s \n  Base Value: 0x%02x \n  No of Operands: %d \n",key,
               it->baseval, it->No_of_Oprnds);
        int i = 0;

        for(i =0; i< it->No_of_Oprnds ; i++) {
            if(*Operands != NULL) {
                printf("Operand %d brkts :%d \t",i, (*Operands)->brkts);
                printf("enc_val: %d \t",(*Operands)->enc_val);
                printf("open_val: %d \n", (*Operands)->open_val);
                Operands++;
            }
        }
    }
    else {
        printf("Command %s details not found\n", key);
    }
    return;
}

/* Interface to add a command to the hashtable of supported commands */

bool addCommand(char* key, struct Command* cmd) {

    if(key == NULL || cmd == NULL)
        return false;
//                  printf("addCommand called :%d, %d \n", cmd->baseval, cmd->No_of_Oprnds);
    ENTRY e, *ep;
    e.key = key;
    e.data = (void*) cmd;
    ep = hsearch(e, ENTER);
    if(ep == NULL) {
        printf(" Hash table insert failed\n");
        return false;
    }
    //printEntry(key);
    return true;
}

/* Some of the common command type  -- Performs 1 Operation
   and takes one Byte Instruction  Eg: HALT instruction */
struct Command* Ops1Bytes1(int init) {

    struct Command* cmd = Init_Command(init,0,NULL);
    if( cmd == NULL)  goto end;
    return cmd;
end:
    return NULL;
}

/* Instruction with one Operation and takes two bytes instruction
   Eg: NOT A;
*/
struct Command* Ops1Bytes2(int init) {
    struct Oprnd* op1 = init_operand(0,0,0);
    if(op1 == NULL) goto end;

    struct Oprnd** opnds = (struct Oprnd**)malloc(sizeof(struct Oprnd*));
    if(opnds == NULL) goto end;
    *opnds = op1;
    struct Command* cmd = Init_Command(init,1,opnds);
    if( cmd == NULL) goto end;
    return cmd;
end:
    return NULL;
}

/*Command with 2 Operations and two bytes of instruction
  Ex: RANDOM a */

struct Command* Ops2Bytes2(int init) {
    struct Oprnd* op1 = init_operand(1,0,1);
    if(op1 == NULL) goto end;

    struct Oprnd** opnds = (struct Oprnd**)malloc(sizeof(struct Oprnd*));
    if(opnds == NULL) goto end;
    *opnds = op1;

    struct Command* cmd = Init_Command(init,1,opnds);
    if( cmd == NULL)  goto end;
    return cmd;
end:
    return NULL;
}

/*Command with 2 Operations and takes 3 Byte Instructions
  Ex: AND, OR,XOR .. */

struct Command* Ops2Bytes3(int init) {
    struct Oprnd* op1 = init_operand(0,0,0);
    if(op1 == NULL) goto end;
    struct Oprnd* op2 = init_operand(1,0,1);
    if(op2 == NULL) goto end;

    struct Oprnd** opnds = (struct Oprnd**)malloc(2*sizeof(struct Oprnd*));
    if(opnds == NULL) goto end;
    *opnds = op1;
    opnds++;
    *opnds = op2;
    opnds--;
    struct Command* cmd = Init_Command(init,2,opnds);
    if( cmd == NULL)  goto end;

//                  printf("Command initilaised: %d and %d \n", cmd->baseval, cmd->No_of_Oprnds);
    int i;
    //opnds = (struct Oprnd**)cmd->Ops;
#if 0
    for(i =0; i< cmd->No_of_Oprnds ; i++) {
        printf("Operand %d brkts :%d \t",i, (*opnds)->brkts);
        printf("Operand %d enc_val: %d \t", i,(*opnds)->enc_val);
        printf("Operand %d open_val: %d \n", i, (*opnds)->open_val);
        opnds++;
    }
#endif
    return cmd;
end:
    return NULL;
}


struct Command* Ops4Bytes2(int init) {

    struct Oprnd* op1 = init_operand(1,0,1);
    if(op1 == NULL) goto end;
    struct Oprnd** opnds = (struct Oprnd**)malloc(sizeof(struct Oprnd*));
    *opnds = op1;

    if(opnds == NULL) goto end;
    struct Command* cmd = Init_Command(init,1,opnds);
    if( cmd == NULL)  goto end;
    return cmd;
end:
    return NULL;
}

struct Command* Ops4Bytes3(int init) {
    struct Oprnd* op1 = init_operand(1,0,2);
    if(op1 == NULL) goto end;
    struct Oprnd* op2 = init_operand(1,0,2);
    if(op2 == NULL) goto end;

    struct Oprnd** opnds = (struct Oprnd**)malloc(2*sizeof(struct Oprnd*));
    *opnds = op1;
    opnds++;
    *opnds = op2;
    opnds--;
    if(opnds == NULL) goto end;
    struct Command* cmd = Init_Command(init,2,opnds);
    if( cmd == NULL)  goto end;
    return cmd;
end:
    return NULL;
}

struct Command* Ops4Bytes4(int init) {
    struct Oprnd* op1 = init_operand(1,0,1);
    if(op1 == NULL) goto end;
    struct Oprnd* op2 = init_operand(0,0,0);
    if(op2 == NULL) goto end;

    struct Oprnd* op3 = init_operand(1,0,2);
    if(op3 == NULL) goto end;

    struct Oprnd** opnds = (struct Oprnd**)malloc(3*sizeof(struct Oprnd*));
    *opnds = op1;
    opnds++;
    *opnds = op2;
    opnds++;
    *opnds = op3;
    opnds--;
    opnds--;
    if(opnds == NULL) goto end;
    struct Command* cmd = Init_Command(init,3,opnds);
    if( cmd == NULL)  goto end;
    return cmd;
end:
    return NULL;
}

/* Function to delete the command from the data base */
void DeleteCommand(struct Command* cmd ) {

    if(cmd == NULL)
        return;

    int i;
    struct Oprnd** p = cmd->Ops;
    for(i =0; i < cmd->No_of_Oprnds; i++) {
        free(*p);
        p++;
    }
    free(cmd);
}

/* Function to build up the database of the instructions -- called
   from the main at the startup */
bool CmdDbInit() {

    hcreate(16);
    ENTRY e, *ep;
    char* key;
    struct Command* cmd;
    /*AND function */
    key = getKey("AND");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes3(00)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("OR");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes3(02)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("XOR");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes3(04)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("NOT");
    if(key == NULL)
        return false;
    if((cmd = Ops1Bytes2(06)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("MOV");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes3(07)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;


    key = getKey("RANDOM");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes2(9)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("ADD");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes3(10)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("SUB");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes3(12)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("JMP");
    if(key == NULL)
        return false;
    if((cmd = Ops2Bytes2(14)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("JZ");
    if(key == NULL)
        return false;
    if((cmd = Ops4Bytes3(16)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("JEQ");
    if(key == NULL)
        return false;
    if((cmd = Ops4Bytes4(20)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("JLS");
    if(key == NULL)
        return false;
    if((cmd = Ops4Bytes4(24)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("JGT");
    if(key == NULL)
        return false;
    if((cmd = Ops4Bytes4(28)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("HALT");
    if(key == NULL)
        return false;
    if((cmd = Ops1Bytes1(255)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("APRINT");
    if(key == NULL)
        return false;
    if((cmd = Ops4Bytes2(32)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    key = getKey("DPRINT");
    if(key == NULL)
        return false;
    if((cmd = Ops4Bytes2(34)) == NULL)
        return false;
    if(addCommand(key, cmd) == false)
        return false;

    return true;
}
