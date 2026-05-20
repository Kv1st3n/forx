#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

void identifyFile(FILE *input, FILE *output);
void scanDirectory(const char *dir_name, FILE *output);
long int fileSize(FILE *input);

#endif 


