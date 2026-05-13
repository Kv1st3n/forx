#ifndef HEXDUMPER_H
#define HEXDUMPER_H

#include <stdio.h>

void dumpHex(FILE *file, FILE *output);
void reverseDump(FILE *file_name, FILE *output);
void convertReversedHexToAscii(char *ptr, char *ascii_col, FILE *output);

#endif 
