#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "hexDumper.h"

int main(int argc, char **argv) {

    FILE *file = fopen(argv[1], "rb");

    if (!file) {
        perror("fopen");
        return 1;
    }

    dumpHex(file);

    fclose(file);
    return 0;
}