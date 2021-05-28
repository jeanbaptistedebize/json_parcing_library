#ifndef MY_ERROR_H_
#define MY_ERROR_H_

#include <errno.h>

// ___ Error_fonc ___ //
int exit_error(const char *error, int exit_code);

// ___ Constance define ___ //
static const int EXIT_ERROR =         84;
static const char *ERROR_SYNTAX_JSON =  "Error syntax in file\n";
static const char *ERROR_SYNTAX_ID =  "Error syntax in data name\n";
static const char *ERROR_SYNTAX_END_OBJ =  "Error syntax in EO_OBJ\n";
static const char *ERROR_SYNTAX_BOOL  =  "Error syntax in Boolean\n";



#endif