#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "hexDumper.h"

typedef uint8_t u8;

#define MIN_LENGTH 4

void dump_hex(FILE *input, FILE *output, int lower_case, int compact, int byteOutput) {

    u8 buf[16];
    size_t n, offset = 0;

    while ((n = fread(buf, 1, 16, input)) > 0) {

        if (lower_case == 1) {
            fprintf(output, "%08zx  ", offset);
        } else {
            fprintf(output, "%08zX  ", offset);
        }

        for (size_t i = 0; i < 16; i++) {
            if (i < n) {
                fprintf(output, lower_case ? "%02x " : "%02X ", buf[i]);
            } else {
                fprintf(output, "   "); 
            }
            if (i == 7) {
                fprintf(output, " ");
            }
        }

        if (compact == 0) {
            fprintf(output, " |");
            for (size_t i = 0; i < n; i++) {
                fprintf(output, "%c", isprint(buf[i]) ? buf[i] : '.');
            }
            fprintf(output, "|\n");
            offset += n;
        } else {
            fprintf(output, "\n");
            offset += n;
        }
    }

    if (byteOutput == 1) {
        fprintf(output, "\n%zu bytes\n", offset);
    }
}

void reverse_dump(FILE *file_name, FILE *output) { 

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

        convert_reversed_hex_to_ascii(ptr, ascii_col, output);

    }
} 

void convert_reversed_hex_to_ascii(char *ptr, char *ascii_col, FILE *output) {
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


void extract_strings(FILE *input, FILE *output) {
    int byte;
    long byteOffset = 0;
    char *buffer = malloc(sizeof(char) * 4); 
    size_t bufferCapacity = (sizeof(char) * 4);
    size_t runLength = 0;
    size_t runStart = 0;


    while ((byte = fgetc(input)) != EOF) {

        if (isprint(byte)) {

            if (runLength == 0) {
                runStart = byteOffset;
            }

            if (runLength >= bufferCapacity - 1) {
                bufferCapacity *= 2;
                buffer =  realloc(buffer, bufferCapacity);
            }

            buffer[runLength] = byte;
            runLength++;

        } else {
            
            if (runLength >= MIN_LENGTH) {
                buffer[runLength] = '\0';
                fprintf(output, "%08lX  %s\n", runStart, buffer);
            }
            runLength = 0;

        }
        byteOffset++;

    }

    if (runLength >= MIN_LENGTH) {
        buffer[runLength] = '\0';
        fprintf(output, "%08lX  %s\n", runStart, buffer);
    }

    free(buffer);
}

