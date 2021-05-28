#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_error.h"
#include "struct_json.h"
#include "json_fonc.h"

void print_js(json_t *json_data);
char *fill_buffe_from_file(char *argv);

int check_type(const char c)
{
    if (isdigit(c))
        return JSONInteger;
    switch (c) {
        case '"':
            return JSONstring;
            break;
        case '{':
            return JSONObject;
            break;
        case '[':
            return JSONArray;
            break;
        case 't':
        case 'f':
            return JSONBoolean;
            break;
        default:
            return JSONError;
    }
}

void get_json_type(char **buffer, int *type)
{
    while (**buffer == ' ' || **buffer == '\n')
        (*buffer)++;
    if (**buffer == '\0')
        exit_error(ERROR_SYNTAX_JSON, EXIT_ERROR);
    *type = check_type(**buffer);
    if (*type == -1)
        exit_error(ERROR_SYNTAX_JSON, EXIT_ERROR); 
}

int get_obj_size(char *buffer, char c_tofind)
{
    int size_obj = 1;
    int nbr_braquette = 1;

    for (; *buffer != '\0' && nbr_braquette > 0; buffer += 1) {
        if (*buffer == c_tofind && nbr_braquette == 1)
            size_obj += 1;
        if (*buffer == '{' || *buffer == '[') {
            nbr_braquette += 1;
        } else if (*buffer == ']' || *buffer == '}')
            nbr_braquette -= 1;
    }
    return size_obj;
}

json_t *get_ellement_data(signed char type, char **buffer, char *id)
{
    return fonc_type[type].fonc(buffer, id);
}

bool check_ellement_end(char **buffer, char c)
{
    if (**buffer == ',')
        return EXIT_SUCCESS;
    *buffer = get_start_string_json(*buffer, c);
    return EXIT_SUCCESS;
}

json_t *get_json_obj(char **buffer, char *id)
{
    json_t *json_data = malloc(sizeof(json_t));
    char *temp;
    int temp_type;

    (*buffer)++;
    json_data->data = calloc(get_obj_size(*buffer, ':'), sizeof(void *));
    json_data->id = id;
    json_data->type = JSONObject;
    for (int i = 0; **buffer != '}' && **buffer; i++, (*buffer)++) {
        *buffer = get_start_string_json(*buffer, '"');
        if (**buffer == '/') {
            for (; **buffer != '\n' && **buffer; (*buffer)++);
            i--;
            continue;
        }
        (*buffer)++;
        get_string_json(buffer, &temp);
        if (**buffer != ':')
            exit_error(ERROR_SYNTAX_JSON, EXIT_ERROR);
        (*buffer)++;
        get_json_type(buffer, &temp_type);
        json_data->data[i] = get_ellement_data(temp_type, buffer, temp);
        check_ellement_end(buffer, '}');
        if (**buffer == '}')
            break;
    }
    (*buffer)++;
    return json_data;
}

json_t *get_json_array(char **buffer, char *id)
{
    json_t *json_data = malloc(sizeof(json_t));
    char *temp;
    int temp_type;

    (*buffer)++;
    json_data->data = calloc(get_obj_size(*buffer, '{'), sizeof(void *));
    json_data->id = id;
    json_data->type = JSONArray;
    for (int i = 0; **buffer != ']' && **buffer; i++, (*buffer)++) {
        *buffer = get_start_string_json(*buffer, '{');
        json_data->data[i] = get_json_obj(buffer, strdup(id));
        check_ellement_end(buffer, ']');
        if (**buffer == ']')
            break;
    }
    (*buffer)++;
    return json_data;
}

json_t *parce_json(char *json_path)
{
    json_t *json_data;
    char *buffer = fill_buffe_from_file(json_path);
    char *head __attribute__((__cleanup__(free_string))) = buffer;
    char *temp = "data";

    json_data = get_json_obj(&buffer, strdup(temp));
    return json_data;
}