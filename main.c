#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "hexDumper.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: hexdumper <file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");

    if (!file) {
        perror("fopen");
        return 1;
    }

    dumpHex(file);

    fclose(file);
    return 0;
}