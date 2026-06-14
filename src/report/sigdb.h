#ifndef SIGDB_H
#define SIGDB_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus

#include <vector>
#include <string>

struct Signature {
    uint8_t     sig[16];
    size_t      len;
    std::string name;
};

class SignatureDB {

private:
    std::vector<Signature> signatures;

public:
    SignatureDB() = default;
    ~SignatureDB() = default;

    void        load_file(const std::string &path);
    const char *identify_file(const uint8_t *buf, size_t len) const;
    int         count_signatures() const;
    void        clear_signatures();
    void        reload(const std::string &path);
};

#endif


#ifdef __cplusplus
extern "C" {
#endif

void        sigdb_load(const char *path);
const char *sigdb_identify(const uint8_t *buf, size_t len);
int         sigdb_count(void);
void        sigdb_reload(const char *path);

#ifdef __cplusplus
}
#endif

#endif