#pragma once

#include <ulfius.h>
#include "utils/errors.hpp"

mbbk_error_t mbbk_route_user_create(const struct _u_request *request,
                                    struct _u_response *response,
                                    void *user_data);


mbbk_error_t mbbk_route_user_get_all(const struct _u_request *request,
                                    struct _u_response *response,
                                    void *user_data);