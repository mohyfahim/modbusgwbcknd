
#include "utils/utils.hpp"

#include <jansson.h>
#include <mbedtls/sha256.h>

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "utils/errors.hpp"


std::string mbbk_utils_hash_password(const std::string &password) {
  mbedtls_sha256_context ctx;
  mbedtls_sha256_init(&ctx);
  mbedtls_sha256_starts(&ctx, 0);

  mbedtls_sha256_update(
      &ctx, reinterpret_cast<const unsigned char *>(password.c_str()),
      password.length());

  unsigned char hash[32]; // SHA-256 produces a 32-byte hash
  mbedtls_sha256_finish(&ctx, hash);
  mbedtls_sha256_free(&ctx);

  // Convert the hash to a hexadecimal string
  char hashStr[65]; // Each byte is represented by two characters, plus the null
                    // terminator
  for (int i = 0; i < 32; i++) {
    sprintf(&hashStr[i * 2], "%02x", hash[i]);
  }
  hashStr[64] = '\0';

  return hashStr;
}

