#include "file_handler.h"
#include <string>
#include <stdexcept>
#include <cstdio>


BinaryFile::BinaryFile(const std::string &path) {
    file = fopen(path.c_str(), "rb");
    if (!file)
        throw std::runtime_error("cannot open: " + path);
    fseek(file, 0, SEEK_END);
    _size = (size_t)ftell(file);
    ::rewind(file);
}

BinaryFile::~BinaryFile() {
    if (file) {
        fclose(file);
        file = nullptr;
    }
}

bool BinaryFile::is_open() const noexcept {
    return file != nullptr;
}

size_t BinaryFile::read_file(uint8_t *buf, size_t n) {
    return fread(buf, 1, n, file);
}


int BinaryFile::peek_file(uint8_t *buf, size_t n) {
    size_t pos = tell();
    size_t got = read_file(buf, n);

    seek_file(pos);
    return (int)got;
}

void BinaryFile::seek_file(size_t offset) {
    fseek(file, (long)offset, SEEK_SET);
}

void BinaryFile::rewind_file() {
    ::rewind(file);
}

size_t BinaryFile::tell() const {
    return (size_t)ftell(file);
}

size_t BinaryFile::file_size() const {
    return _size;
}

bool BinaryFile::eof() const {
    return tell() >= _size;
}

FILE *BinaryFile::raw() const {
    return file;
}

// C bridge
BinaryFileHandle *bfile_open(const char *path) {
    try {
        return reinterpret_cast<BinaryFileHandle *>(new BinaryFile(path));
    } catch (...) {
        return nullptr;
    }
}

void bfile_close(BinaryFileHandle *h) {
    delete reinterpret_cast<BinaryFile *>(h);
}

FILE *bfile_raw(BinaryFileHandle *h) {
    return reinterpret_cast<BinaryFile *>(h)->raw();
}

void bfile_seek(BinaryFileHandle *h, size_t offset) {
    reinterpret_cast<BinaryFile *>(h)->seek_file(offset);
}

size_t bfile_size(BinaryFileHandle *h) {
    return reinterpret_cast<BinaryFile *>(h)->file_size();
}
