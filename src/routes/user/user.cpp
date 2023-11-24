#include <iostream>

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include "utils/utils.hpp"

mbbk_error_t mbbk_route_user_create(const struct _u_request *request,
                                    struct _u_response *response,
                                    void *user_data) {


  UserModel user{-1, "Paul", "Password"};
  user.id = mbbk_storage.insert(user);
  ulfius_set_string_body_response(response, 200,
                                  mbbk_utils_generate_resp(true, "NULL", 200));
  return U_CALLBACK_CONTINUE;
}

mbbk_error_t mbbk_route_user_get_all(const struct _u_request *request,
                                     struct _u_response *response,
                                     void *user_data) {
  Json::Value root;
  Json::Value arr(Json::arrayValue);

  auto users = mbbk_storage.get_all<UserModel>();

  for (auto &user : users) {
    Json::Value elm;
    elm["username"] = user.username;
    elm["id"] = user.id;
    arr.append(elm);
  }
  root["users"] = arr;

  ulfius_set_string_body_response(response, 200,
                                  mbbk_utils_generate_resp(true, root, 200));

  return U_CALLBACK_CONTINUE;
}