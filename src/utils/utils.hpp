#pragma once
#ifndef _MBBK_UTILS_H_
#define _MBBK_UTILS_H_

#include <json/json.h>

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "utils/errors.hpp"

#define MBBK_DB_PATH "/var/run/mbbk.db"

inline auto mbbk_storage = sqlite_orm::make_storage(
    MBBK_DB_PATH,
    sqlite_orm::make_table(
        "user",
        sqlite_orm::make_column("id", &UserModel::id,
                                sqlite_orm::primary_key()),
        sqlite_orm::make_column("name", &UserModel::username),
        sqlite_orm::make_column("abilities", &UserModel::password)));

// template <class T> class MbbkDbHandler {
// public:
//   MbbkDbHandler(T init) : storage(init) {}
//   T storage;
// };

// template <class T> class MbbkGlobal : public MbbkDbHandler<T> {
// public:
//   MbbkGlobal(T init) : MbbkDbHandler(init) {}
// };

template <class T>
const char *mbbk_utils_generate_resp(bool success, T data, int code) {
  Json::Value resp;
  resp["success"] = success;
  if (success) {
    resp["result"] = data;
  } else {
    resp["message"] = data;
  }
  resp["code"] = code;

  Json::StreamWriterBuilder builder;
  return Json::writeString(builder, resp).c_str();
}

#endif