#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct_json.h"
#include "my_error.h"

json_t *get_ellement_string(char **buffer, char *id)
{
    json_t *json_data = malloc(sizeof(json_t));
    char *temp;

    (*buffer)++;
    json_data->type = JSONstring;
    json_data->id = id;
    json_data->data = malloc(sizeof(void *));
    get_string_json(buffer, &temp);
    json_data->data[0] = temp;
    return json_data;
}

void get_string_bool(char **buffer, void **str)
{
    if (!strncmp(*buffer, "true", 4)) {
        *str = malloc(sizeof(char) * 5);
        strcpy(*str, "true");
        (*buffer) += 4;
    } else {
        *str = malloc(sizeof(char) * 6);
        strcpy(*str, "false");
        (*buffer) += 5;
    }
}

json_t *get_ellement_bool(char **buffer, char *id)
{
    json_t *json_data = malloc(sizeof(json_t));

    if (strncmp(*buffer, "true", 4) && strncmp(*buffer, "false", 5))
        exit_error(ERROR_SYNTAX_BOOL, EXIT_ERROR);
    json_data->type = JSONBoolean;
    json_data->id = id;
    json_data->data = malloc(sizeof(void *));
    get_string_bool(buffer, json_data->data);
    return json_data;
}

static char *scan_nbr(char *str, int *nbr)
{
    long nb = 0;
    int signe = 1;

    if (str == NULL){return str;}
    while ('0' <= *str && *str <= '9' && *str != '\0') {
        nb *= 10;
        nb += (*str - 48);
        str++;
    }
    *nbr = nb * signe;
    return str;
}

json_t *get_ellement_number(char **buffer, char *id)
{
    json_t *json_data = malloc(sizeof(json_t));
    int i = 0;
    void *temp;

    for (; isdigit(buffer[0][i]); i++);
    if (buffer[0][i] == '.') {
        temp = malloc(sizeof(float));
        json_data->type = JSONFloat;
    } else {
        json_data->type = JSONInteger;
        temp = malloc(sizeof(int));
    }
    json_data->id = id;
    json_data->data = malloc(sizeof(void *));
    *buffer = scan_nbr(*buffer, temp);
    json_data->data[0] = temp;
    return json_data;
}