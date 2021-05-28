#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int exit_error(const char *error, int exit_code)
{
    write(2, error, strlen(error));
    exit(exit_code);
}