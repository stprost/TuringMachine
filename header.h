//
// Created by pk on 12.06.2018.
//

#ifndef TURINGMACHINE_HEADER_H
#define TURINGMACHINE_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mem.h>
#include <stdbool.h>

#define MIN_LEN_OF_TAPE 10

struct Cond {
    char *prevSymb;
    char *nextSymb;
    char *move;
    int nextCond;
};

int in(FILE *inputOne, FILE *inputTwo, FILE *output);

void printTapes(char **arrayOfTapes, int numOfTapes, int tapesLen[numOfTapes], int arrayOfPointers[numOfTapes], FILE *output);

void printCommands(struct Cond **q, int maxQ, int *sizeOfColumns, int numOfTapes, FILE *output);

void printCommand(struct Cond **q,int numOfTapes, int row, int col, FILE *output);

#endif //TURINGMACHINE_HEADER_H
