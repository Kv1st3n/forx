#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "hexDumper.h"

int main(int argc, char **argv) {

    int flag_h = 0;
    int flag_r = 0;
    int opt;
    while((opt = getopt(argc, argv, "hCLr")) != -1) {

        switch(opt){
            case 'h': flag_h = 1; break;
            case 'r': flag_r = 1; break;
            case 'C':
                break;
            case 'L':
                break;
            case '?':
                fprintf(stderr, "unknown flag: -%c\n", optopt);
                return EXIT_FAILURE;

        }
    }

    FILE *file;

    if (optind < argc) {
        file = fopen(argv[optind], "rb");
        if (!file) { 
            perror("fopen"); return EXIT_FAILURE; 
        }

    } else {
        file = stdin;
    }

    if (flag_h) {
        dumpHex(file);
    }

    if (flag_r) {
        reverseDump(file);
    }

    if (file != stdin) {
        fclose(file);
    }

    return EXIT_SUCCESS;
}