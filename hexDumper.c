#include <stdio.h>
#include <stdint.h>
#include "hexDumper.h"
#include <ctype.h>
#include <string.h>

void dumpHex(FILE *file, FILE *output, int lower_case) {

    uint8_t buf[16];
    size_t n, offset = 0;

    while ((n = fread(buf, 1, 16, file)) > 0) {

        if (lower_case == 1) {
            fprintf(output, "%08zx  ", offset);
        } else {
            fprintf(output, "%08zX  ", offset);
        }

        for (size_t i = 0; i < n; i++) {

            if (i < n) {

                if (lower_case == 1) {
                    fprintf(output, "%02x ", buf[i]);
                } else {
                    fprintf(output, "%02X ", buf[i]);
                }
                
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

void reverseDump(FILE *file_name, FILE *output) { 

    char fileLine[256];

    while (fgets(fileLine, sizeof(fileLine), file_name) != NULL) {

        // safeguard to ensure the code reads the hex values
        if (strlen(fileLine) < 10 || fileLine[8] != ' ') {
            continue;
        }

        char *ptr = strchr(fileLine, ' ');
        if (!ptr) {
            continue;
        }

        char *ascii_col = strchr(fileLine, '|');
        if (!ascii_col) {
            continue;
        }

        convertReversedHexToAscii(ptr, ascii_col, output);

    }
} 

void convertReversedHexToAscii(char *ptr, char *ascii_col, FILE *output) {
    while (ptr < ascii_col) {
            if (isspace((unsigned char)*ptr)) {
                ptr++;
                continue;
            }

            unsigned char byte;
            if (sscanf(ptr, "%2hhX", &byte) == 1) {
                fwrite(&byte, 1, 1, output);
                ptr += 2;
            } else {
                ptr++;
            }
        }
}

