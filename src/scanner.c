#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "signatures.h"
#include "scanner.h"

typedef uint8_t u8;
typedef int32_t i32;

void identify_file(FILE *input, FILE *output) {
    u8 buffer[16];
    size_t n = fread(buffer, 1, 16, input);
    rewind(input);
    long int size = file_size(input);

    for (size_t i = 0; i < SINGATURE_COUNT; i++) {
        if (n >= database[i].len &&
            memcmp(buffer, database[i].sig, database[i].len) == 0) {
            fprintf(output, "Type: %s | Size: %ld bytes\n",
                    database[i].name, size);
            return;
        }
    }

    fprintf(output, "Type: Unknown | Magic: %02X %02X %02X %02X | Size: %ld bytes\n",
            buffer[0], buffer[1], buffer[2], buffer[3], size);
}

long int file_size(FILE *input) {

    fseek(input, 0L, SEEK_END);

    i32 size = ftell(input);
    rewind(input);
    return size;

}


void scan_directory(const char *dir_name, FILE *output) {

    DIR *dir = opendir(dir_name);
    struct dirent *entry;

    if (dir == NULL) {
        printf("Could not open the directory\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        struct stat path_stat;
        
        if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
            scan_directory(path, output);
        } else {
            FILE *fp = fopen(path, "rb");

            if (!fp) { 
                perror(path); continue; 
            }

            fprintf(output, "%s: ", path);
            identify_file(fp, output);
            fclose(fp);
        }

    }

    closedir(dir);
} 

