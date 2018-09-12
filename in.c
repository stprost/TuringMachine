#include "header.h"


int in(FILE *inputOne, FILE *inputTwo, FILE *output, int argc, char *argv[]) {

    //считывание количества лент и состояний машины
    int prevQ, nextQ, ret, numOfTapes, rowQ;
    char *strPrevSymb, *strNextSymb, *strMove, *token, *last;

    fscanf(inputOne, "%d", &numOfTapes);
    if (numOfTapes <= 0) {
        printf("error 200: Wrong number of tapes");
        exit(200);
    }
    int len = numOfTapes * 2;
    struct Cond **q;
    int maxQ = 1;
    int *sizeOfColumns;
    q = (struct Cond **) calloc(maxQ + 1, sizeof(struct Cond *));
    sizeOfColumns = (int *) calloc(maxQ + 1, sizeof(int));
    for (int i = 1; i < maxQ + 1; i++) {
        q[i] = (struct Cond *) calloc(1, sizeof(struct Cond));
        sizeOfColumns[i] = 1;
    }
    char tempLine[9 + 6 * numOfTapes];
    while (1) {
        fscanf(inputOne, "\n");
        ret = fgets(tempLine, sizeof(tempLine), inputOne);
        if (ret == 0) break;
        strPrevSymb = (char *) calloc(len, sizeof(char));
        strNextSymb = (char *) calloc(len, sizeof(char));
        strMove = (char *) calloc(len, sizeof(char));
        token = strtok_r(tempLine, " []", &last);
        prevQ = strtol(token, NULL, 0);
        if (prevQ == 0) {
            printf("error 201: Incorrect input conditions data");
            exit(201);
        }
        token = strtok_r(NULL, " []", &last);
        if (strlen(token) != len - 1) {
            printf("error 201: Incorrect input conditions data");
            exit(201);
        }
        strcpy(strPrevSymb, token);
        token = strtok_r(NULL, " []", &last);
        nextQ = strtol(token, NULL, 0);
        token = strtok_r(NULL, " []", &last);
        if (strlen(token) != len - 1) {
            printf("error 201: Incorrect input conditions data");
            exit(201);
        }
        strcpy(strNextSymb, token);
        token = strtok_r(NULL, " []", &last);
        if (strlen(token) != len - 1) {
            printf("error 201: Incorrect input conditions data");
            exit(201);
        }
        strcpy(strMove, token);
        token = strtok_r(NULL, " []\n", &last);
        if (token != NULL) {
            printf("error 201: Incorrect input conditions data");
            exit(201);
        }

        if (nextQ > maxQ) {
            maxQ = nextQ;
            q = (struct Cond **) realloc(q, (maxQ + 1) * sizeof(struct Cond *));
            sizeOfColumns = (int *) realloc(sizeOfColumns, (maxQ + 1) * sizeof(int));
            for (int i = prevQ + 1; i <= maxQ; i++) {
                q[i] = (struct Cond *) calloc(1, sizeof(struct Cond));
                sizeOfColumns[i] = 1;
            }
        }

        q[prevQ] = (struct Cond *) realloc(q[prevQ], (sizeOfColumns[prevQ] + 1) * sizeof(struct Cond));

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
    fclose(inputOne);


    //считывание начального состояния лент
    char **arrayOfTapes, tempChar, tempTape[100];
    int count, arrayOfPointers[numOfTapes], tapesLen[numOfTapes];
    bool flag;
    arrayOfTapes = (char **) calloc(numOfTapes, sizeof(char *));
    for (int i = 0; i < numOfTapes; i++) {
        arrayOfTapes[i] = (char *) calloc(MIN_LEN_OF_TAPE, sizeof(char));
        tapesLen[i] = MIN_LEN_OF_TAPE;
    }
    for (int i = 0; i < numOfTapes; i++) {
        fscanf(inputTwo, "%s", tempTape);
        if (strcmp(tempTape, "empty") == 0 || strcmp(tempTape, "Empty") == 0) {
            arrayOfPointers[i] = 0;
            for (int j = 0; j < MIN_LEN_OF_TAPE; j++) {
                arrayOfTapes[i][j] = '_';
            }
            continue;
        }
        count = 0;
        flag = false;
        while (tempTape[count] != '\0') {
            if (tempTape[count] == 'v' || tempTape[count] == 'V') {
                flag = true;
                arrayOfPointers[i] = count;
                break;
            } else if (tempTape[count] != '_') {
                printf("error 202: Incorrect input tapes data");
                exit(202);
            }
            count++;
        }
        if (!flag) {
            printf("error 202: Incorrect input tapes data");
            exit(202);
        }
        fscanf(inputTwo, "\n");
        fscanf(inputTwo, "%s", tempTape);
        while (strlen(tempTape) > tapesLen[i]) {
            tapesLen[i]++;
            arrayOfTapes[i] = (char *) realloc(arrayOfTapes[i], tapesLen[i] * sizeof(char));
        }
        strcpy(arrayOfTapes[i], tempTape);
        free(tempTape);
    }

    if (argc == 6 && (strcmp(argv[5], "-p")) == 0) {
        printf("Tapes:\n");
        fprintf(output, "Tapes:\n");
        printTapes(arrayOfTapes, numOfTapes, tapesLen, arrayOfPointers, output);
        printCommands(q, maxQ, sizeOfColumns, numOfTapes, output);

    }
    bool debug = false;
    if (strcmp(argv[4], "-o") == 0) debug = true;
    step(arrayOfTapes, numOfTapes, arrayOfPointers, tapesLen, q, debug, sizeOfColumns, output);
    //printf("%s %s %s %d", q[1][0].prevSymb, q[1][0].nextSymb, q[1][0].move, q[1][0].nextCond);
}