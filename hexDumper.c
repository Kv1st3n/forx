#include <stdio.h>
#include <stdint.h>
#include "hexDumper.h"
#include <ctype.h>

void dumpHex(FILE *file) {

    uint8_t buf[16];
    size_t n, offset = 0;

    while ((n = fread(buf, 1, 16, file)) > 0) {
        printf("%08zX  ", offset);

        for (size_t i = 0; i < n; i++) {

            if (i < n) {
                printf("%02X ", buf[i]);
            } else {
                printf("   "); 
            }
            if (i == 7) {
                printf(" ");
            }
        }
        
        printf(" |");
        for (size_t i = 0; i < n; i++) {
            printf("%c", isprint(buf[i]) ? buf[i] : '.');
        }
        printf("|\n");
        offset += n;

    }
    printf("\n%zu bytes\n", offset);

}