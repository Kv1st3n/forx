#ifndef HEXDUMPER_H
#define HEXDUMPER_H

#include <stdio.h>

void dump_hex(FILE *input, FILE *output, int lower_case, int compact, int byteOutput);
void reverse_dump(FILE *file_name, FILE *output);
void convert_reversed_hex_to_ascii(char *ptr, char *ascii_col, FILE *output);
void extract_strings(FILE *input, FILE *output);

#endif 
