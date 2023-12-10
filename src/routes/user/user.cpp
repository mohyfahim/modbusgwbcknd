#include <iostream>
#include <jansson.h>

#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "user.hpp"
#include "utils/utils.hpp"

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
      std::string session_token = mbbk_utils_generate_token(15);
      std::string refresh_token = mbbk_utils_generate_token(43200);
      json_object_set_new(js, "refresh", json_string(refresh_token.c_str()));
      json_object_set_new(js, "session", json_string(session_token.c_str()));
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
          std::string session_token = mbbk_utils_generate_token(15);
          std::string refresh_token = mbbk_utils_generate_token(43200);
          json_object_set_new(js, "refresh",
                              json_string(refresh_token.c_str()));
          json_object_set_new(js, "session",
                              json_string(session_token.c_str()));
          json_t *out = mbbk_utils_generate_resp(true, js, 200);
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

mbbk_error_t mbbk_route_check_token_middleware(const struct _u_request *request,
                                               struct _u_response *response,
                                               void *user_data) {
  std::pair<std::string, mbbk_error_t> err = mbbk_utils_extract_token(request);
  if (err.second == MBBK_FAIL) {
    MBBK_UTILS_ERROR_MSG("Authorization failed", 401);
    return U_CALLBACK_UNAUTHORIZED;
  } else {
    return U_CALLBACK_CONTINUE;
  }
}

mbbk_error_t mbbk_route_user_get_auth(const struct _u_request *request,
                                      struct _u_response *response,
                                      void *user_data) {

  return U_CALLBACK_CONTINUE;
}

mbbk_error_t mbbk_route_user_refresh_auth(const struct _u_request *request,
                                          struct _u_response *response,
                                          void *user_data) {
  return U_CALLBACK_CONTINUE;
}