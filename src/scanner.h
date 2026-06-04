#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

void identify_file(FILE *input, FILE *output);
void scan_directory(const char *dir_name, FILE *output);
long int file_size(FILE *input);

#endif 


