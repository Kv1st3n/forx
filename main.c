#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "hexDumper.h"
#include "scanner.h"

int main(int argc, char **argv) {

    int   flag_h = 0;
    int   flag_o = 0;
    int   flag_r = 0;
    int   flag_C = 0;
    int   compact = 0;
    int   flag_L = 0;
    int   lower_case = 0;
    int   flag_i = 0;
    int   flag_d = 0;
    const char  *dir_name;


    char *outpath = NULL;
    int   opt;
    
    while ((opt = getopt(argc, argv, "hiod:rCL")) != -1) {
        switch (opt) {
            case 'h':
                flag_h = 1;
                break;
            case 'i':
                flag_i = 1;
                break;
            case 'o':
                flag_o  = 1;
                outpath = optarg;
                break;
            case 'r':
                flag_r = 1;
                break;
            case 'C':
                flag_C = 1;
                break;
            case 'L':
                flag_L = 1;
                break;
            case 'd':
                flag_d = 1;
                break;
            default:
                fprintf(stderr, "usage: hexDumper [-h] [-o outfile] <file>\n");
                return EXIT_FAILURE;
        }
    }

    FILE *input;

    if (optind < argc) {
        input = fopen(argv[optind], "rb"); 
        if (!input) { perror("fopen input"); return EXIT_FAILURE; }
    } else {
        input = stdin;
    }

    FILE *output;

    if (flag_o && outpath) {
        output = fopen(outpath, "w");
        if (!output) { perror("fopen output"); return EXIT_FAILURE; }
    } else {
        output = stdout;
    }

    if (flag_L) {
        lower_case = 1;
    }

    if (flag_C) {
        compact = 1;
    }

    if (flag_i)
        identifyFile(input, output);

    if (flag_h)
        dumpHex(input, output, lower_case, compact);

    if (flag_r)
        reverseDump(input, output);

    if (!flag_i && !flag_h && !flag_r) {
        fprintf(stderr, "usage: hexDumper [-h] [-i] [-o outfile] [-r] <file>\n");
        return EXIT_FAILURE;
    }

    if (flag_d) {
        scanDirectory(dir_name, input, output);
    }

    if (input != stdin)  {
        fclose(input);
    }

    if (output != stdout) {
        fclose(output);
    }

    return EXIT_SUCCESS;
} 
