/*
** EPITECH PROJECT, 2021
** jsonlib
** File description:
** get data
*/

#include <string.h>
#include "struct_json.h"

void *find_data_json(void **data, const char *id)
{
    json_t *cur;
    int i = 0;

    for (; *data; data++) {
        cur = *data;
        if (!strcmp(cur->id, id))
            break;
    }
    if (!(*data))
        return data;
    return cur->data;
}

int json_get_int(json_t *value, char *key)
{
    return *(int *)(*(void **)(find_data_json(value->data, key)));
}

float json_get_float(json_t *value, char *key)
{
    return *(float *)(*(void **)(find_data_json(value->data, key)));
}

char *json_get_string(json_t *value, char *key)
{
    return (*(void **)(find_data_json(value->data, key)));
}