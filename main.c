#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "hexDumper.h"
#include "scanner.h"

int main(int argc, char **argv) {

    int   flag_hexDump = 0;
    int   flag_output = 0;
    int   flag_reverseHex = 0;
    int   flag_Compact = 0;
    int   compact = 0;
    int   flag_LowerCase = 0;
    int   lower_case = 0;
    int   flag_identify = 0;
    int   flag_directoryScan = 0;
    int   flag_hexByteOutput = 0;
    const char  *dir_name;


    char *outpath = NULL;
    int   opt;
    
    while ((opt = getopt(argc, argv, "hio:d:BrCL")) != -1) {
        switch (opt) {
            case 'h':
                flag_hexDump = 1;
                break;
            case 'i':
                flag_identify = 1;
                break;
            case 'o':
                flag_output  = 1;
                outpath = optarg;
                break;
            case 'B':
                flag_hexByteOutput = 1;
                break;
            case 'r':
                flag_reverseHex = 1;
                break;
            case 'C':
                flag_Compact = 1;
                break;
            case 'L':
                flag_LowerCase = 1;
                break;
            case 'd':
                flag_directoryScan = 1;
                dir_name = optarg;
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

    if (flag_output && outpath) {
        output = fopen(outpath, "w");
        if (!output) { perror("fopen output"); return EXIT_FAILURE; }
    } else {
        output = stdout;
    }

    // rewrite / improve <- feels redundant
    if (flag_LowerCase) {
        lower_case = 1;
    }

    // rewrite / improve <- feels redundant
    if (flag_Compact) {
        compact = 1;
    }

    if (flag_directoryScan) {
        scanDirectory(dir_name, output);
    }

    if (flag_identify) {
        identifyFile(input, output);
    }

    if (flag_hexDump) {
        dumpHex(input, output, lower_case, compact, flag_hexByteOutput);
    }

    if (flag_reverseHex) {
        reverseDump(input, output);
    }

    // maybe update
    if (!flag_directoryScan && !flag_identify && !flag_hexDump && !flag_reverseHex) {
        fprintf(stderr, "usage: hexDumper [-h] [-i] [-d dir] [-o outfile] [-r] <file>\n");
        return EXIT_FAILURE;
    }

    if (input != stdin)  {
        fclose(input);
    }

    if (output != stdout) {
        fclose(output);
    }

    return EXIT_SUCCESS;
} 
