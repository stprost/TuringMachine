#include "header.h"

int main() {
    char a[10] = "qwe", *tok, *las;
    tok = strtok_r(a, "v", &las);
    printf("%d", strlen(a));
    tok = strtok_r(NULL, "v", &las);
    if (a == NULL) printf("fail");

    FILE *file;
    //считывание количества лент и состояний машины
    int prevQ;
    int nextQ;
    char *strPrevSymb;
    char *strNextSymb;
    char *strMove;
    int ret;
    int numOfTapes;

    file = fopen("../input.txt", "r");
    fscanf(file, "%d", &numOfTapes);
    if (numOfTapes == 0) {
        printf("Wrong number of tapes.");
        exit(1);
    }
    int len = numOfTapes * 2;
    struct Cond **q;
    int sizeOfLines = MIN_COND;
    int *sizeOfColumns;
    q = (struct Cond **) calloc(sizeOfLines, sizeof(struct Cond *));
    sizeOfColumns = (int *) calloc(sizeOfLines, sizeof(int));
    for (int i = 0; i < sizeOfLines; i++) {
        q[i] = (struct Cond *) calloc(1, sizeof(struct Cond));
        sizeOfColumns[i] = 1;
    }
    char tempLine[9 + 6 * numOfTapes];
    while (1) {
        fscanf(file, "\n");
        ret = fgets(tempLine, sizeof(tempLine), file);
        if (ret == 0) break;
        strPrevSymb = (char *) calloc(len, sizeof(char));
        strNextSymb = (char *) calloc(len, sizeof(char));
        strMove = (char *) calloc(len, sizeof(char));
        char *token, *last;
        token = strtok_r(tempLine, " []", &last);
        prevQ = strtol(token, NULL, 0);
        if (prevQ == 0) {
            printf("Incorrect input conditions data");
            exit(2);
        }
        token = strtok_r(NULL, " []", &last);
        if (strlen(token) != len - 1) {
            printf("Incorrect input conditions data");
            exit(2);
        }
        strcpy(strPrevSymb, token);
        token = strtok_r(NULL, " []", &last);
        nextQ = strtol(token, NULL, 0);
        token = strtok_r(NULL, " []", &last);
        if (strlen(token) != len - 1) {
            printf("Incorrect input conditions data");
            exit(2);
        }
        strcpy(strNextSymb, token);
        token = strtok_r(NULL, " []", &last);
        if (strlen(token) != len - 1) {
            printf("Incorrect input conditions data");
            exit(2);
        }
        strcpy(strMove, token);
        token = strtok_r(NULL, " []\n", &last);
        if (token != NULL) {
            printf("Incorrect input conditions data");
            exit(2);
        }


        if (prevQ + 1 > sizeOfLines) {
            q = (struct Cond **) realloc(q, (prevQ + 1) * sizeof(struct Cond *));
            sizeOfColumns = (int *) realloc(sizeOfColumns, (prevQ + 1) * sizeof(int));
            for (int i = sizeOfLines; i < prevQ + 1; i++) {
                q[i] = (struct Cond *) calloc(1, sizeof(struct Cond));
                sizeOfColumns[i] = 1;
            }
            sizeOfLines = prevQ + 1;
        }
        int n = prevQ; //строка
        int m = sizeOfColumns[prevQ] - 1; //столбец
        q[n][m].nextCond = nextQ;
        q[n][m].prevSymb = (char *) calloc(numOfTapes + 1, sizeof(char));
        q[n][m].nextSymb = (char *) calloc(numOfTapes + 1, sizeof(char));
        q[n][m].move = (char *) calloc(numOfTapes + 1, sizeof(char));
        int i = 0;
        token = strtok_r(strPrevSymb, " ,", &last);
        while (token != NULL) {
            strcat(q[n][m].prevSymb, token);
            token = strtok_r(NULL, " ,", &last);
            i++;
        }
        i = 0;
        token = strtok_r(strNextSymb, " ,", &last);
        while (token != NULL) {
            strcat(q[n][m].nextSymb, token);
            token = strtok_r(NULL, " ,", &last);
            i++;
        }
        i = 0;
        token = strtok_r(strMove, " ,", &last);
        while (token != NULL) {
            strcat(q[n][m].move, token);
            token = strtok_r(NULL, " ,", &last);
            i++;
        }
        sizeOfColumns[n]++;
        q[n] = (struct Cond *) realloc(q[n], sizeOfColumns[n] * sizeof(struct Cond));
        free(strPrevSymb);
        free(strNextSymb);
        free(strMove);
    }
    fclose(file);
    printf("%s %s %s %d", q[2][0].prevSymb, q[2][0].nextSymb, q[2][0].move, q[2][0].nextCond);


    //считывание начального состояния лент
//    char **arrayOfTapes, tempChar;
//    int count, arrayOfPointers[numOfTapes];
//    boolean flag;
//    arrayOfTapes = (char **) calloc(numOfTapes, sizeof(char *));
//    for(int i = 0; i < numOfTapes; i++){
//        arrayOfTapes = (char *) calloc(MIN_LEN_OF_TAPE, sizeof(char));
//    }
//    file = fopen("../tapes.txt", "r");
//    for (int i = 0; i < numOfTapes; i++) {
//        count = 0;
//        flag = false;
//        while (tempChar != '\n') {
//            fscanf(file, "%c", &tempChar);
//            if (tempChar == 'v' || tempChar == 'V') {
//                flag = true;
//                arrayOfPointers[i] = count;
//                break;
//            } else if (tempChar != '_') {
//                printf("Incorrect input data");
//                exit(3);
//            }
//            count++;
//        }
//        if (!flag) {
//            printf("Incorrect input data");
//            exit(3);
//        }
//        fscanf(file, "\n");
//        fscanf(file, "%c", tempChar);
//        while (tempChar != '\n'){
//
//        }
//
//
//    }
}