#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus

#include <string>
#include <stdexcept>

class BinaryFile {
    FILE *fp = nullptr;
    size_t _size = 0;

public:
    BinaryFile(const std::string &path);
    ~BinaryFile();

    BinaryFile(const BinaryFile&) = delete;
    BinaryFile &operator=(const BinaryFile&) = delete;

    bool is_open();
    size_t read_file(uint8_t *buf, size_t n);
    int peek_file(uint8_t *buf, size_t n);
    void seek_file(size_t offset);
    void rewind();
    size_t tell();
    size_t size();
    bool eof();
    FILE *raw();


};


extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif