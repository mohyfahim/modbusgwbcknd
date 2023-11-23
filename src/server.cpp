
#include <iostream>
#include <stdio.h>
#include <string>
#include <ulfius.h>

#include "routes/routes.hpp"
#include "utils/utils.hpp"

#include "sqlite_orm/sqlite_orm.h"

#define PORT 8085

/**
 * main function
 */
int main(void) {
  struct _u_instance instance;
  mbbk_storage.sync_schema();
  // Initialize instance with the port number
  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort\n");
    return (1);
  }

  // Endpoint list declaration
  mbbk_register_routes(&instance, NULL);
  // Start the framework
  if (ulfius_start_framework(&instance) == U_OK) {
    printf("Start framework on port %d\n", instance.port);

    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  } else {
    fprintf(stderr, "Error starting framework\n");
  }
  printf("End framework\n");

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);

  return 0;
}