#include <stdio.h>
#include <stdint.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

typedef uint8_t u8;

// todo, update these with the non-deprecated ones

void printMD5Checksum(FILE *input, FILE *output) {
    u8 buf[4096];
    size_t len;
    u8 md5Digest[MD5_DIGEST_LENGTH];
    MD5_CTX md5ctx;

    MD5_Init(&md5ctx);

    while ((len = fread(buf, 1, sizeof(buf), input)) > 0) {
        MD5_Update(&md5ctx, buf, len);
    }

    MD5_Final(md5Digest, &md5ctx);

    fprintf(output, "MD5:      ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        fprintf(output, "%02x", md5Digest[i]);
    }
    fprintf(output, "\n");
    fflush(output);
}

void printSHA1Checksum(FILE *input, FILE *output) {
    u8 buf[4096];
    size_t len;
    u8 sha1Digest[SHA_DIGEST_LENGTH];
    SHA_CTX sha1ctx;

    SHA1_Init(&sha1ctx);

    while ((len = fread(buf, 1, sizeof(buf), input)) > 0) {
        SHA1_Update(&sha1ctx, buf, len);
    }

    SHA1_Final(sha1Digest, &sha1ctx);

    fprintf(output, "SHA1:     ");
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        fprintf(output, "%02x", sha1Digest[i]);
    }
    fprintf(output, "\n");
}

void printSHA256Checksum(FILE *input, FILE *output) {
    u8 buf[4096];
    size_t len;
    u8 sha256Digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256ctx;

    SHA256_Init(&sha256ctx);

    while ((len = fread(buf, 1, sizeof(buf), input)) > 0) {
        SHA256_Update(&sha256ctx, buf, len);
    }

    SHA256_Final(sha256Digest, &sha256ctx);

    fprintf(output, "SHA256:   ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(output, "%02x", sha256Digest[i]);
    }
    fprintf(output, "\n");
} 

 