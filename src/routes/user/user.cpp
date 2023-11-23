#include "user.hpp"
#include "models/users.hpp"
#include "sqlite_orm/sqlite_orm.h"
#include "utils/utils.hpp"

mbbk_error_t mbbk_route_user_create(const struct _u_request *request,
                                    struct _u_response *response,
                                    void *user_data) {

  // MbbkGlobal *mbbg = (MbbkGlobal *)user_data;

  UserModel user{-1, "Paul", "Password"};
  user.id = mbbk_storage.insert(user);
  ulfius_set_string_body_response(response, 200,
                                  mbbk_utils_generate_resp(true, "NULL", 200));
  return U_CALLBACK_CONTINUE;
}