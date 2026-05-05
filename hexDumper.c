#include <stdio.h>
#include <stdint.h>
#include "hexDumper.h"

void dumpHex(const char *file_name) {

    uint8_t buf[16];
    size_t n, offset = 0;

    // read the file and print out the hexes
    while ((n = fread(buf, n, offset, file_name)) > 0) {
        
    }


    return 0;
}