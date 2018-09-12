#include "header.h"

void inf() {
    printf("Turing simulator\nto run the program type in command line\nTuring.exe input1.txt input2.txt output.txt -a/-o"
           " [-p]\n-a runs the program,\n-o runs debug,\n-p gives you information about your input data."
           "\ninput1.txt should contain such commands:\na[x1,x2,...,xn]  b[y1,y2,...,yn][D1,D2,...,Dn], where a and b are the numbers of temporary and next states of machine\n"
           "[x1,x2,...,xn] and [y1,y2,...,yn] are the symbols on the tape\n[D1,D2,...,Dn] are the direction of move (L - left, R - right, _ - no move, "
           "S - stop).\ninput2.txt should contain the initial tape in such structure:\n__v___\n100001\n___v__\n100321\nif "
           "you run debug\ns - one step,\nb - break,\nf - follow the program in standart mode.\nExample:"
           "\ninput1.txt\n2\n"
           "1[0,0] 2[1,1][R,R]\n"
           "2[1,1] 3[_,0][_,R]\n"
           "2[0,1] 2[0,1][L,_]\n"
           "3[_,0] 2[1,1][R,S]\n"
           "input2.txt\n__v___\n"
           "100001\n"F
           "_v____\n"
           "101010\n"
           "output.txt\nTapes:\n"
           "__v___\n"
           "100001\n"
           "_v____\n"
           "101010\n"
           "Running command\n"
           "1[0,0] 2[1,1][R,R]\n"
           "Tapes:\n"
           "___v__\n"
           "101001\n"
           "__v___\n"
           "111010\n"
           "Running command\n"
           "2[0,1] 2[0,1][L,_]\n"
           "Tapes:\n"
           "__v___\n"
           "101001\n"
           "__v___\n"
           "111010\n"
           "Running command\n"
           "2[1,1] 3[_,0][_,R]\n"
           "Tapes:\n"
           "__v___\n"
           "10_001\n"
           "___v__\n"
           "110010\n"
           "Running command\n"
           "3[_,0] 2[1,1][R,S]\n"
           "Tapes:\n"
           "___v__\n"
           "101001\n"
           "___v__\n"
           "110110\n"
           "End of program");
}

void main(int argc, char *argv[]) {
    FILE *inputOne;
    FILE *inputTwo;
    FILE *output;

    if (argc == 1) {
        inf(); // информация о программе
        exit(0);
    }

    if ((argc == 5) && (strcmp(argv[4], "-a") == 0 || strcmp(argv[4], "-o") == 0) ||
        ((argc == 6) && (strcmp(argv[4], "-a") == 0 || strcmp(argv[4], "-o") == 0) && (strcmp(argv[5], "-p") == 0))) {

        inputOne = fopen(argv[1], "rt");

        if (inputOne == NULL) {
            printf("error 100: Can not find first input file\n");
            exit(100);
        }

        inputTwo = fopen(argv[2], "rt");
        if (inputTwo == NULL) {
            printf("error 101: Can not find second input file\n");
            exit(101);
        }

        output = fopen(argv[3], "w");
        if (output == NULL) {
            printf("Can not find output file\n");
        }
    }

    if (argc != 5) {
        if (argc != 6 || (argc == 6 && (strcmp(argv[5], "-p") != 0))) {
            printf("error 102: Wrong number of arguments\n");
            exit(102);
        }
    }

    in(inputOne, inputTwo, output, argc, argv);

    exit(0);
}