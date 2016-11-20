#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "jmvm.h"

int main(int argc, char *argv[]) 
{
    //prints 10 to the console
    instr program[] = {
        {PUSH, 10},
        {PINT, 0},
        {DONE, 0}
    };
    return 0;
}


