#include <stdio.h>
#include <stdint.h>
#include "hexDumper.h"
#include <ctype.h>

#define UNUSED(x) (void)(x)

void dumpHex(FILE *file, FILE *output) {

    uint8_t buf[16];
    size_t n, offset = 0;

    while ((n = fread(buf, 1, 16, file)) > 0) {
        fprintf(output, "%08zX  ", offset);

        for (size_t i = 0; i < n; i++) {

            if (i < n) {
                fprintf(output, "%02X ", buf[i]);
            } else {
                fprintf(output, "   "); 
            }
            if (i == 7) {
                fprintf(output, " ");
            }
        }
        
        fprintf(output, " |");
        for (size_t i = 0; i < n; i++) {
            fprintf(output, "%c", isprint(buf[i]) ? buf[i] : '.');
        }
        fprintf(output, "|\n");
        offset += n;

    }
    fprintf(output, "\n%zu bytes\n", offset);

}

void reverseDump(FILE *file_name) { 
    UNUSED(file_name);
    printf("test"); 
} 
