#include <vector>
#include <string>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstring>
#include "sigdb.h"

static SignatureDB &instance() {
    static SignatureDB db;
    return db;
}

void SignatureDB::load_file(const std::string &path) {
    std::ifstream file(path);

    if (!file) {
        std::cerr << "sigdb: cannot open " << path << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {

        if (line.empty() || line[0] == '#') {
            continue;
        }

        Signature entry;
        entry.len = 0;

        std::istringstream ss(line);
        std::string token;

        while (ss >> token) {
            
            if (token.length() <= 2 && std::all_of(token.begin(), token.end(), ::isxdigit)) {
                entry.sig[entry.len++] = (uint8_t)std::stoul(token, nullptr, 16);
            } else {

                std::string rest;
                std::getline(ss, rest);
                entry.name = token + rest;
                break;
            }
        }
        
        if (entry.len > 0 && !entry.name.empty())
            signatures.push_back(entry);
    }
    
};

const char *SignatureDB::identify_file(const uint8_t *buf, size_t len) const {
    for (const auto &entry : signatures) {
        if (len >= entry.len && memcmp(buf, entry.sig, entry.len) == 0) {
            return entry.name.c_str();  
        }
    }
    return "Unknown";
}

int SignatureDB::count_signatures() const {
    size_t number_of_signatures = signatures.size();

    return number_of_signatures;
}

void SignatureDB::clear_signatures() {
    signatures.clear();
}


void SignatureDB::reload(const std::string &path) {
    clear_signatures();
    load_file(path);
}


void sigdb_load(const char *path) {
    instance().load_file(path);
}

const char *sigdb_identify(const uint8_t *buf, size_t len) {
    return instance().identify_file(buf, len);
}

int sigdb_count(void) {
    return instance().count_signatures();
}

void sigdb_reload(const char *path) {
    instance().reload(path);
}