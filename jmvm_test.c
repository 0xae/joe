#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "jmvm.h"

int func_j(int a, int b) {
    instr program[] = {
        {PUSH, b},
        {PUSH, a},
        {MUL, 0},
        {STORE, 0},

        {PUSH, 10},
        {PUSH, 100},
        {DIV, 0},
        {POP, 0},
        {SWP, 0},
        {SUB, 0},
        {STORE, 0},

        {PUSH, 15},
        {PUSH, b},
        {DIV, 0},
        {POP, 0},
        {ADD, 0},
        {STORE, 0},

        {DONE, 0}
    };
    int count = instr_count(program);
    run_func(program, count);
    return r3;
}

int func_t(int a, int b) {
    return a*b - (10/100) + 15/b;
}

int main(int argc, char *argv[]) {
    int x = func_j(1,2);
    int y = func_t(1,2);
    printf("got=%d,  expected=%d\n", x, y);
    return 0;
}
