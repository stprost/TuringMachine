#include "header.h"

void inf() {
    printf("Turing simulator\nto run the program type in command line\nTuring.exe input1.txt input2.txt output.txt -a/-o"
           " [-p]\n-a runs the program,\n-o runs debug,\n-p gives you information about your input data."
           "\ninput1.txt should contain such commands:\n-aqn-bqkD, where a and b are the symbols on the tape (the"
           " first state is always q1),\nqn"
           " and qk are the states of machine,\nD is the direction of move (L - left, R - right, H - no move,"
           " S - stop).\ninput2.txt should contain the initial tape in such structure:\n_____v____\n1210392910\nif"
           " you run debug\ns - one step,\nb - break,\nf - follow the program in standart mode.\nExample:"
           "\ninput1.txt\n-0q1-1q1L\n-1q1-1q1L\n-2q1-1q1S\ninput2.txt\n__v__\n20101\noutput.txt\nTape\n__v__\n20101"
           "\nRunning command\n1q1-1q1L\nTape\n_v___\n20101\nRunning command\n0q1-1q1L\nTape\nv____\n21101"
           "\nRunning command\n2q1-1q1S\nTape\nv____\n11101\n");
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

        output = fopen(argv[3], "wr");
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