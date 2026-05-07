#include <stdio.h>
#include <stdint.h>
#include "hexDumper.h"

void dumpHex(FILE *file) {

    uint8_t buf[16];
    size_t n, offset = 0;

    // read the file and print out the hexes
    while ((n = fread(buf, 1, 16, file)) > 0) {
        printf("%08zX  ", offset);

        for (size_t i = 0; i < n; i++) {
            printf("%02X ", buf[i]);
        }
        printf("\n"); 
        offset += n;

    }
}