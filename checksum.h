#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdio.h>

void printMD5Checksum(FILE *file, FILE *output);
void printSHA1Checksum(FILE *file, FILE *output);
void printSHA256Checksum(FILE *file, FILE *output);

#endif 

 