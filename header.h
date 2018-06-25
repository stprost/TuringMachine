//
// Created by pk on 12.06.2018.
//

#ifndef TURINGMACHINE_HEADER_H
#define TURINGMACHINE_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mem.h>
#include <rpcndr.h>
#include <stdbool.h>

#define MIN_COND 2
#define MIN_LEN_OF_TAPE 10

struct Cond {
    char *prevSymb;
    char *nextSymb;
    char *move;
    int nextCond;
};

#endif //TURINGMACHINE_HEADER_H
