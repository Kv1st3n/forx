#include <vector>
#include <string>
#include <cstdio>
#include "sigdb.h"

SignatureDB::SignatureDB(const std::string &path) {

}

SignatureDB::~SignatureDB() {

}

void load_file();

void identify_file();

int count_signatures();

void clear_vector(const std::vector<Signature>& signatures);

void relaod();