#pragma once

#include "utils/errors.hpp"
#include <ulfius.h>

mbbk_error_t mbbk_route_user_create(const struct _u_request *request,
                                    struct _u_response *response,
                                    void *user_data);

mbbk_error_t mbbk_route_user_login(const struct _u_request *request,
                                   struct _u_response *response,
                                   void *user_data);

mbbk_error_t mbbk_route_user_get_auth(const struct _u_request *request,
                                      struct _u_response *response,
                                      void *user_data);

mbbk_error_t mbbk_route_user_refresh_auth(const struct _u_request *request,
                                      struct _u_response *response,
                                      void *user_data);
                                      
mbbk_error_t mbbk_route_check_token_middleware(const struct _u_request *request,
                                               struct _u_response *response,
                                               void *user_data);