#pragma once

#include <json/json.h>

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "utils/errors.hpp"

#define MBBK_DB_PATH "/usr/share/mbbk.db"

extern inline auto mbbk_storage = sqlite_orm::make_storage(
    MBBK_DB_PATH,
    sqlite_orm::make_table(
        "user",
        sqlite_orm::make_column("id", &UserModel::id,
                                sqlite_orm::primary_key()),
        sqlite_orm::make_column("name", &UserModel::username),
        sqlite_orm::make_column("password", &UserModel::password)));

template <class T>
std::string mbbk_utils_generate_resp(bool success, T data, int code) {
  Json::Value resp;
  resp["success"] = success;
  if (success) {
    resp["result"] = data;
  } else {
    resp["message"] = data;
  }
  std::string resp_s = Json::FastWriter().write(resp);
  return resp_s;
}
