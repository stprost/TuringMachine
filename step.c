
#include "header.h"

int
step(char **arrayOfTapes, int numOfTapes, int arrayOfPointers[numOfTapes], int tapesLen[numOfTapes], struct Cond **q,
     bool debug, int *sizeOfColumns, FILE *output) {
    int quit = 0, count;
    int tempCond = 1;
    char tempTapeSymb[numOfTapes];
    bool flag, stop = false;
    printTapes(arrayOfTapes, numOfTapes, tapesLen, arrayOfPointers, output);
    while (quit != 1000) {
        flag = false;
        //поиск подходящего состояния
        for (int i = 0; i < sizeOfColumns[tempCond] - 1; i++) {
            count = 0;
            for (int j = 0; j < numOfTapes; j++) {
                if (arrayOfTapes[j][arrayOfPointers[j]] != q[tempCond][i].prevSymb[j]) {
                    continue;
                }
                count++;
            }
            if (count == numOfTapes) {
                flag = true;
                for (int j = 0; j < numOfTapes; j++) {
                    arrayOfTapes[j][arrayOfPointers[j]] = q[tempCond][i].nextSymb[j];
                    switch (q[tempCond][i].move[j]) {
                        case 'L':
                            arrayOfPointers[j]--;
                            break;
                        case 'R':
                            arrayOfPointers[j]++;
                            break;
                    }
                    if (arrayOfPointers[j] == tapesLen[j]) {
                        tapesLen[j]++;
                        arrayOfTapes[j] = (char *) realloc(arrayOfTapes[j], tapesLen[j] * sizeof(char));
                        if (arrayOfTapes[j] == NULL) {
                            printf("error 400: Memory allocation error\n");
                            exit(400);
                        }
                        arrayOfTapes[j][tapesLen[j] - 1] = '_';
                    }
                    if (arrayOfPointers[j] < 0) {
                        printf("error 401: Head index out of bounds\n");
                        exit(401);
                    }
                    if (q[tempCond][i].move[j] == 'S') {
                        stop = true;
                    }
                }
                printCommand(q, numOfTapes, tempCond, i, output);
                printTapes(arrayOfTapes, numOfTapes, tapesLen, arrayOfPointers, output);
                tempCond = q[tempCond][i].nextCond;
                break;
            }
        }
        if (!flag) {
            printf("error 404: Condition not found");
            exit(404);
        }
        if (stop) {
            printf("End of program\n");
            fprintf(output, "End of program\n");
            break;
        }
        if (debug) { //если выбран режим отладки
            char comand[2];
            while (1) {
                scanf(" %2s", comand);
                fflush(stdin); //очистка буфера
                if (!strcmp(comand, "b")) {
                    printf("Program break\n");
                    fclose(output);
                    exit(403);
                }
                if (!strcmp(comand, "s")) {
                    break;
                }
                if (!strcmp(comand, "f")) {
                    debug = false;
                    break;
                } else printf("No such instruction. Enter other\n");
            }
        }
        quit++;
        if (quit == 1000) {
            printf("error 402: Runtime error\n");
            exit(402);
        }
    }
}

