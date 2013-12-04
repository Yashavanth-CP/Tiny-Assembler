#include<stdio.h>
#include<stdlib.h>
#include"Command.h"
#include"Operand.h"
#include<stdbool.h>
#include<string.h>

/* main entrance of the program */

int main() {

    /* Initiate the Instructions Database */
    bool ret = CmdDbInit();
    if(ret == false) {
        printf("Initialisation failed\n");
        return 0;
    }

    /* Open the input file for reading and converting */
    FILE* ip = fopen("./sampleip.txt", "r");
    if(ip == NULL) {
        printf("Opening of file failed\n");
        return 0;
    }

    /* Tokenise the input read line and send it for processing */
    char line[80];
    char* token;
    char** toSend = (char**)malloc(sizeof(char*)*4);  /* An array of character pointers to send as an arguement
                                                                to the Processing function */
    if(toSend == NULL) {
        printf("Malloc failed \n");
        return 0;
    }

    char** it; /* Iterator to iterate over toSend character array */
    int count; // holds information of the number of tokens from the line */

    while(fgets(line, 80, ip) != NULL) {

        it = toSend;
        count =0;
        line[strlen(line)-1] = '\0'; /* remove the new line character from the line, since we are using fgets */

        token = strtok(line, " "); /* tokenise the line with space character as delimiter */

        while(token != NULL) {
            *it = (char*)malloc(strlen(token)* sizeof(char));
            if(*it == NULL) {
                printf("Arguments read failed \n");
                return 0;
            }
            strcpy(*it, token);
            it++;
            count++;
            token = strtok(NULL, " ");
        }

        int base = -1; /* Base value */

        if(count != 0) { /*if the line is not an Empty line */
//          printf("Called Process_ins with value %d \n", count);
            base = Process_ins(toSend, count);
        }

        if(base == -1) { /* The returned base value is not a valid */
            printf("%s\n", "Wrong Instruction format");
            continue;
        }
        else if(base == -2) { /* Instruction not present in database */
            printf("%s \n", "Not a valid Instruction");
            continue;
        }
        else { /* Everything normal */
            printf("0x%02x  ", base);
        }

        int i ;
        it = toSend;
        // printf("Count is %d \n", count);

        if(count > 1)
            it++;

        /* Print the codes for the operands only and not instruction */
        for(i = 1; i < count; i++) {
            if(strlen(*it) == 1)
                printf("0x%02x  ", **it - '0');
            else
                printf("0x%02x  ", *((*it)+1) - '0');

            it++;
        }
        printf("\n");
    }
    return 0;
}

