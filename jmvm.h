#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAX_INSTR 200

// @Interface

enum jmvm_instruction_set {
    ADD, SUB, MUL, DIV,
    PUSH, POP, STORE, SWP,
    IFEQJ, IFGTJ, IFGTEJ, IFLTJ, IFLTEJ,
    INVK, LOG, PINT,
    NOP , DBG, DONE
};

typedef struct {
    int type;
    int arg;
} instr;

void run_func(instr program[], int len) ;
int instr_count(instr program[]);


// @Implementation

static int r[2] = {0, 0};
static int gr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static int r3=0;
static int rp=0;

int instr_count(instr program[]){
    int t = 0;
    for(; program[t].type != DONE; t++);
    return t;
}

void run_func(instr program[], int len) {
    int k, tmp=0;
    for(k=0; k<len; k++) {
        instr i = program[k];
        switch(i.type){
            case STORE:
                r3=r[0];
                rp=0;
                break;
            case PUSH:
                if (rp > 1) { puts("register-overflow\n"); exit(1); }
                r[rp++]=i.arg;
                break;
            case POP:
                if (rp > 1) { puts("register-overflow\n"); exit(1); }
                r[rp++]=r3;
                break;
            case ADD:
                r[0]=r[0]+r[1];
                rp=1;
                break;
            case SUB:
                r[0]=r[0]-r[1];
                rp=1;
                break;
            case DIV:
                r[0]=r[0]/r[1];
                rp=1;
                break;
            case MUL:
                r[0]=r[0]*r[1];
                rp=1;
                break;
            case SWP:
                tmp=r[0];
                r[0]=r[1];
                r[1]=tmp;
                break;
            case DBG:
                printf("r=[%d, %d], rp=%d, r3=%d\n", 
                        r[0], r[1], rp, r3);
                break;
            case PINT:
                printf("%d\n", r[0]);
                break;
            default:
                puts("INVALID-INSTRUCTION\n"); 
                exit(1);
        }
    }
}

