
#include "header.h"

int step(char **arrayOfTapes, int numOfTapes, int arrayOfPointers[numOfTapes], struct Cond **q, int sizeOfLines,
         int *sizeOfColumns) {
    int quit = 0, count, tempCond;
    char tempTapeSymb[numOfTapes];
    bool flag = false;
    while (quit != 1000) {
        //поиск подходящего состояния по присутствующим в лентах символам
        for (int i = 0; i < sizeOfColumns[tempCond]; i++) {
            count = 0;
            for (int j = 0; j < numOfTapes; j++) {
                if (arrayOfTapes[j][arrayOfPointers[j]] == q[tempCond][i].prevSymb[j]) count++;
            }
            if (count != numOfTapes) continue;
            //замена символов в ленте
            for (int j = 0; j < numOfTapes; j++) {
                arrayOfTapes[j][arrayOfPointers[j]] == q[tempCond][i].prevSymb[j];
            }
            flag = true;
        }
    }
}

