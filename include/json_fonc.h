#ifndef JSON_FONC_H
#define JSON_FONC_H

#include "struct_json.h"

// ___ ellement_fonc ___
json_t *get_json_obj(char **buffer, char *id);
json_t *get_json_array(char **buffer, char *id);
json_t *get_ellement_string(char **buffer, char *id);
json_t *get_ellement_bool(char **buffer, char *id);
json_t *get_ellement_number(char **buffer, char *id);

typedef struct fonc_type_s
{
    json_t *(*fonc)(char **buffer, char *id);
}fonc_type_s;

static fonc_type_s fonc_type[] = {
    {NULL},
    {NULL},
    {&get_ellement_string},
    {&get_ellement_number},
    {&get_ellement_number},
    {&get_json_obj},
    {&get_json_array},
    {&get_ellement_bool}
    };

#endif