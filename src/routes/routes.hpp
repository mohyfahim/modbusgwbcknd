#pragma once

#include <ulfius.h>

#include "user/user.hpp"

#define API_PREFIX "/api/"

void mbbk_register_routes(struct _u_instance* instance, void* user_data){


  ulfius_add_endpoint_by_val(instance, "POST", API_PREFIX "user", NULL, 0,
                             &mbbk_route_user_create, user_data);

}