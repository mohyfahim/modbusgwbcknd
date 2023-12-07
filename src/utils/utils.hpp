#pragma once

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "utils/errors.hpp"
#include <jansson.h>

#ifdef DEVELOP
#define MBBK_DB_PATH "mbbk.db"
#else
#define MBBK_DB_PATH "/usr/share/mbbk.db"
#endif

#define MBBK_UTILS_ERROR_MSG(msg, code)                                        \
  do {                                                                         \
    json_t *out = mbbk_utils_generate_resp(false, (const char *)msg, code);    \
    ulfius_set_json_body_response(response, code, out);                        \
    json_decref(out);                                                          \
  } while (0);

std::string mbbk_utils_hash_password(const std::string &password);

extern inline auto mbbk_storage = sqlite_orm::make_storage(
    MBBK_DB_PATH,
    sqlite_orm::make_table(
        "user",
        sqlite_orm::make_column("id", &UserModel::id,
                                sqlite_orm::primary_key()),
        sqlite_orm::make_column("username", &UserModel::username,
                                sqlite_orm::unique()),
        sqlite_orm::make_column("password", &UserModel::password)));

template <class T>
json_t *mbbk_utils_generate_resp(bool success, const T &data, int code) {
  json_t *resp = json_object();
  json_object_set_new(resp, "success", json_boolean(success));
  if (success) {
    if constexpr (std::is_same<T, json_t *>::value) {

      json_object_set_new(resp, "result", data);
    } else {
      json_object_set_new(resp, "result", json_null());
    }
  } else {
    if constexpr (std::is_same<T, const char *>::value) {
      json_object_set_new(resp, "message", json_string(data));
    } else {
      // Handle other types or provide an error message
      json_object_set_new(resp, "message",
                          json_string("Error: Operation failed"));
    }
  }
  json_object_set_new(resp, "code", json_integer(code));
  return resp;
}
