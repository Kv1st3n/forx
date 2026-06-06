#ifdef __cplusplus

#include <string>
#include <cstdio>
#include <stdexcept>

#include "file_handler.h"

class BinaryFile {
    FILE *file = nullptr;
    size_t _size = 0;


public:
    explicit BinaryFile::BinaryFile(const std::string &path) {
        file = fopen(path.c_str(), "rb");

        if (!file) {
            throw std::runtime_error("Failed to open file");
        }

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

    BinaryFile::BinaryFile(const BinaryFile&) = delete;
    BinaryFile &operator=(const BinaryFile&) = delete;  

     // checks if file is open
    bool is_open() const noexcept {
        return file != nullptr;
    }

    // reads n bytes 
    size_t read_file(uint8_t *buf, size_t n);

    // reads n bytes before rewinding, used to identify file by checking the first 16-bytes
    int peek_file(uint8_t *buf, size_t n);

    // moves to an absolute byte position in the file
    void seek_file(size_t offset);

    // goes back to byte 0
    void rewind();

    // returns the current byte position
    size_t tell();

    // returns the file size measured in the constructor
    size_t size();

    // returns true if the current position equals the file size
    bool eof();

    // returns the underlying FILE *
    FILE *raw();

};



#endif