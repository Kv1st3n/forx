#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus

#include <string>
#include <stdexcept>

class BinaryFile {
    FILE *file = nullptr;
    size_t _size = 0;

public:
    BinaryFile(const std::string &path);
    ~BinaryFile();

    BinaryFile(const BinaryFile&) = delete;
    BinaryFile &operator=(const BinaryFile&) = delete;

    bool is_open() const noexcept;
    size_t read_file(uint8_t *buf, size_t n);
    int peek_file(uint8_t *buf, size_t n);
    void seek_file(size_t offset);
    void rewind_file();
    size_t tell() const;
    size_t file_size() const;
    bool eof() const;
    FILE *raw() const;

};

#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BinaryFile BinaryFileHandle;

BinaryFileHandle *bfile_open(const char *path);
void bfile_close(BinaryFileHandle *h);
FILE *bfile_raw(BinaryFileHandle *h);
void bfile_seek(BinaryFileHandle *h, size_t offset);
size_t bfile_size(BinaryFileHandle *h);

#ifdef __cplusplus
}
#endif

#endif
