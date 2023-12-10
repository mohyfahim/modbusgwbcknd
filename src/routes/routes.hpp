#pragma once

#include <ulfius.h>

#include "user/user.hpp"

#define API_PREFIX "/api/"

void mbbk_register_routes(struct _u_instance *instance, void *user_data) {

  ulfius_add_endpoint_by_val(instance, "POST", API_PREFIX, "user", 0,
                             &mbbk_route_user_create, user_data);

  ulfius_add_endpoint_by_val(instance, "POST", API_PREFIX, "login", 0,
                             &mbbk_route_user_login, user_data);

  ulfius_add_endpoint_by_val(instance, "GET", API_PREFIX, "auth", 0,
                             &mbbk_route_check_token_middleware, user_data);

  ulfius_add_endpoint_by_val(instance, "GET", API_PREFIX, "auth", 1,
                             &mbbk_route_user_get_auth, user_data);

  ulfius_add_endpoint_by_val(instance, "POST", API_PREFIX, "auth", 1,
                             &mbbk_route_user_refresh_auth, user_data);
}