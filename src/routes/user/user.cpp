#include <iostream>
#include <jansson.h>
#include <jose/jose.h>

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include "utils/utils.hpp"

const char *secret = "R2F3Z2d1RnlHbE1qU2ROSQ==";

std::string mbbk_utils_generate_token() {
  json_t *jwk = json_object();

  json_object_set_new(jwk, "kty", json_string("oct"));
  json_object_set_new(jwk, "k", json_string(secret));
  json_object_set_new(jwk, "alg", json_string("A128KW"));

  jose_jwk_gen(NULL, jwk);

  json_t* 
}

mbbk_error_t mbbk_route_user_create(const struct _u_request *request,
                                    struct _u_response *response,
                                    void *user_data) {
  json_error_t jse;
  json_t *js = ulfius_get_json_body_request(request, &jse);

  if (js != NULL) {
    json_t *username_j = json_object_get(js, "username");
    json_t *password_j = json_object_get(js, "password");
    std::string username = json_string_value(username_j);
    std::string password = json_string_value(password_j);
    std::string hashed_password = mbbk_utils_hash_password(password);
    UserModel user{-1, username, hashed_password};
    try {
      user.id = mbbk_storage.insert(user);
      json_t *out = mbbk_utils_generate_resp(true, js, 200);
      ulfius_set_json_body_response(response, 200, out);
      json_decref(out);
    } catch (const std::system_error &e) {
      json_t *out =
          mbbk_utils_generate_resp(false, (const char *)e.what(), 400);
      ulfius_set_json_body_response(response, 400, out);
      json_decref(out);
    }

  } else {
    json_t *out =
        mbbk_utils_generate_resp(false, (const char *)"wrong json format", 400);
    ulfius_set_json_body_response(response, 400, out);
    json_decref(out);
  }
  json_decref(js);
  return U_CALLBACK_CONTINUE;
}

mbbk_error_t mbbk_route_user_login(const struct _u_request *request,
                                   struct _u_response *response,
                                   void *user_data) {
  json_error_t jse;
  json_t *js = ulfius_get_json_body_request(request, &jse);

  if (js != NULL) {
    json_t *username_j = json_object_get(js, "username");
    json_t *password_j = json_object_get(js, "password");
    std::string username = json_string_value(username_j);
    std::string password = json_string_value(password_j);
    try {
      auto users = mbbk_storage.get_all<UserModel>(
          sqlite_orm::where(sqlite_orm::c(&UserModel::username) == username));
      if (!users.empty()) {
        std::string hashed_password = mbbk_utils_hash_password(password);
        const UserModel &user = users.front();
        if (user.password == hashed_password) {
          json_auto_t *claim = json_object();
          json_object_set_new(claim, "user") json_t *out =
              mbbk_utils_generate_resp(true, js, 200);
          ulfius_set_json_body_response(response, 200, out);
          json_decref(out);
        } else {
          MBBK_UTILS_ERROR_MSG("wrong user or password", 401);
        }

      } else {
        MBBK_UTILS_ERROR_MSG("wrong user or password", 401);
      }

    } catch (const std::system_error &e) {
      MBBK_UTILS_ERROR_MSG(e.what(), 400);
    }
  } else {
    MBBK_UTILS_ERROR_MSG("wrong json format", 400);
  }
  json_decref(js);
  return U_CALLBACK_CONTINUE;
}

mbbk_error_t mbbk_route_user_get_all(const struct _u_request *request,
                                     struct _u_response *response,
                                     void *user_data) {
  // Json::Value root;
  // Json::Value arr(Json::arrayValue);

  // auto users = mbbk_storage.get_all<UserModel>();

  // for (auto &user : users) {
  //   Json::Value elm;
  //   elm["username"] = user.username;
  //   elm["id"] = user.id;
  //   arr.append(elm);
  // }
  // root["users"] = arr;
  // std::string out = mbbk_utils_generate_resp(true, root, 200);
  ulfius_set_string_body_response(response, 200, "ok");
  return U_CALLBACK_CONTINUE;
}