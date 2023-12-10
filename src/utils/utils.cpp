
#include "utils/utils.hpp"

#include <jansson.h>
#include <mbedtls/sha256.h>

#include "jwt-cpp/jwt.h"
#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "utils/errors.hpp"

#define JWT_SECRET "R2F3Z2d1RnlHbE1qU2ROSQ=="

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

std::string mbbk_utils_generate_token(int min) {
  const auto time = jwt::date::clock::now();
  auto token =
      jwt::create()
          .set_type("JWS")
          .set_issuer("auth0")
          .set_expires_at(time + std::chrono::minutes(min))
          .set_payload_claim("username", jwt::claim(std::string("test")))
          .sign(jwt::algorithm::hs256{JWT_SECRET});
  return token;
}

std::pair<std::string, mbbk_error_t>
mbbk_utils_extract_token(const struct _u_request *req) {

  try {
    std::string token = u_map_get(req->map_header, "Authorization");

    for (std::string::size_type i = 0; i < token.size(); ++i) {
      if (token[i] == ' ') {
        std::string validate = token.substr(0, i);
        std::cout << validate << "," << token.substr(i+1) << std::endl;
        break;
      }
    }
    return std::make_pair(token, MBBK_OK);

  } catch (...) {
    return std::make_pair("", MBBK_FAIL);
  }
}