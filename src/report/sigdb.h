#ifndef SIGDB_H
#define SIGDB_H

#include <vector>
#include <string>


#ifdef __cplusplus

struct Signature {
    std::string type_name;
    std::vector<unsigned char> magic_bytes;
    size_t length;
};

class SignatureDB {

private:
    std::vector<Signature> signatures;


public:

    void load_file();

    void identify_file();

    int count_signatures();

    void clear_vector(const std::vector<Signature>& signatures);

    void relaod();

};


#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif