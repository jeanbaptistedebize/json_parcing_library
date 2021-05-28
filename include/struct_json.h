#ifndef STRUCT_JSON_H
#define STRUCT_JSON_H

#include <stddef.h>

// ___ Const_value ___ //
static const int MAX_STRING_LEN  = 2000;

// ___ Struct ___ //
typedef enum json_value_type {
    JSONError   = -1,
    JSONnull    = 1,
    JSONstring  = 2,
    JSONInteger = 3,
    JSONFloat   = 4,
    JSONObject  = 5,
    JSONArray   = 6,
    JSONBoolean = 7,
} json_value_type;

typedef struct json_s
{
    char *id;
    int type;
    void **data;
} json_t;

char *get_start_string_json(char *buffer, char c);
void get_string_json(char **buffer, char **id);

// ___ ellement_fonc ___ //
json_t *get_json_obj(char **buffer, char *id);
json_t *get_json_array(char **buffer, char *id);
json_t *get_ellement_string(char **buffer, char *id);
json_t *get_ellement_bool(char **buffer, char *id);
json_t *get_ellement_number(char **buffer, char *id);

// ___ find_data ___ //
char *json_get_string(json_t *value, char *key);
void *find_data_json(void **data, char const *id);
float json_get_float(json_t *value, char *key);
int json_get_int(json_t *value, char *key);

// ___ struct ___ //
void print_js(json_t *json_data);
json_t *parce_json(char *filepath_json);
void free_js(json_t *json_data);
void free_string(char **str);

#endif