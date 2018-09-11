
#include "header.h"

void printTapes(char **arrayOfTapes, int numOfTapes, int tapesLen[numOfTapes], int arrayOfPointers[numOfTapes],
                FILE *output) {
    int count;
    for (int i = 0; i < numOfTapes; i++) {
        count = 0;
        while (count <= arrayOfPointers[i]) {
            if (count == arrayOfPointers[i]) {
                printf("v");
                fprintf(output, "v");
            }
            if (count != arrayOfPointers[i]) {
                printf(" ");
                fprintf(output, " ");
            }
            count++;
        }
        printf("\n");
        fprintf(output, "\n");
        count = 0;
        while (arrayOfTapes[i][count] != '\0' && count < tapesLen[i]) {
            printf("%c", arrayOfTapes[i][count]);
            fprintf(output, "%c", arrayOfTapes[i][count]);
            count++;
        }
        printf("\n");
        fprintf(output, "\n");
    }
}

void printCommands(struct Cond **q, int maxQ, int *sizeOfColumns, int numOfTapes, FILE *output) {
    printf("Commands:");
    fprintf(output, "Commands:");
    printf("\n");
    fprintf(output, "\n");
    for (int i = 1; i <= maxQ; i++) {
        for (int j = 0; j < sizeOfColumns[i] - 1; j++) {
            printf("%d[", i);
            fprintf(output, "%d[", i);
            for (int k = 0; k < numOfTapes; k++) {
                printf("%c", q[i][j].prevSymb[k]);
                fprintf(output, "%c", q[i][j].prevSymb[k]);
                if (k != numOfTapes - 1) {
                    printf(",");
                    fprintf(output, ",");
                } else {
                    printf("]");
                    fprintf(output, "]");
                }
            }
            printf(" %d[", q[i][j].nextCond);
            fprintf(output, " %d[", q[i][j].nextCond);
            for (int k = 0; k < numOfTapes; k++) {
                printf("%c", q[i][j].nextSymb[k]);
                fprintf(output, "%c", q[i][j].nextSymb[k]);
                if (k != numOfTapes - 1) {
                    printf(",");
                    fprintf(output, ",");
                } else {
                    printf("]");
                    fprintf(output, "]");
                }
            }
            printf("[");
            fprintf(output, "[");
            for (int k = 0; k < numOfTapes; k++) {
                printf("%c", q[i][j].move[k]);
                fprintf(output, "%c", q[i][j].move[k]);
                if (k != numOfTapes - 1) {
                    printf(",");
                    fprintf(output, ",");
                } else {
                    printf("]");
                    fprintf(output, "]");
                }
            }
            printf("\n");
            fprintf(output, "\n");
        }
    }
    printf("\n");
    fprintf(output, "\n");
}

void printCommand(struct Cond **q, int numOfTapes, int row, int col, FILE *output) {
    printf("Running command");
    fprintf(output, "Running command");
    printf("\n");
    fprintf(output, "\n");
    printf("%d[", row);
    fprintf(output, "%d[", row);
    for (int i = 0; i < numOfTapes; i++) {
        printf("%c", q[row][col].prevSymb[i]);
        fprintf(output, "%c", q[row][col].prevSymb[i]);
        if (i != numOfTapes - 1) {
            printf(",");
            fprintf(output, ",");
        } else {
            printf("]");
            fprintf(output, "]");
        }
    }
    printf(" %d[", q[row][col].nextCond);
    fprintf(output, " %d[", q[row][col].nextCond);
    for (int i = 0; i < numOfTapes; i++) {
        printf("%c", q[row][col].nextSymb[i]);
        fprintf(output, "%c", q[row][col].nextSymb[i]);
        if (i != numOfTapes - 1) {
            printf(",");
            fprintf(output, ",");
        } else {
            printf("]");
            fprintf(output, "]");
        }
    }
    printf("[");
    fprintf(output, "[");
    for (int i = 0; i < numOfTapes; i++) {
        printf("%c", q[row][col].move[i]);
        fprintf(output, "%c", q[row][col].move[i]);
        if (i != numOfTapes - 1) {
            printf(",");
            fprintf(output, ",");
        } else {
            printf("]");
            fprintf(output, "]");
        }
    }
    printf("\n");
    fprintf(output, "\n");
}