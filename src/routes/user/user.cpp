#include <iostream>

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include "utils/utils.hpp"

mbbk_error_t mbbk_route_user_create(const struct _u_request *request,
                                    struct _u_response *response,
                                    void *user_data) {
  std::string req((char *)request->binary_body, request->binary_body_length);
  std::cout << req << std::endl;
  Json::Reader req_j;
  Json::Value root;
  bool err = req_j.parse(req, root);
  if (err) {
    UserModel user{-1, root["username"].asString(),
                   root["password"].asString()};
    user.id = mbbk_storage.insert(user);
    std::string out = mbbk_utils_generate_resp(true, root, 200);
    ulfius_set_string_body_response(response, 200, out.c_str());
  } else {
    ulfius_set_string_body_response(response, 400, "wrong json format");
  }

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
  std::string out = mbbk_utils_generate_resp(true, root, 200);
  ulfius_set_string_body_response(response, 200, out.c_str());
  return U_CALLBACK_CONTINUE;
}