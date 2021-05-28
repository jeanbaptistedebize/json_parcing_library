#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "struct_json.h"
#include "my_error.h"

void print_obj(json_t *json_data, int tab);

void print_ntab(int i)
{
    for (; i > 0; i--, write(1, "\t", 1));
}

void print_string(json_t *json_ttring, int i)
{
    print_ntab(i);
    printf("\"%s\": \"%s\"\n", json_ttring->id, json_ttring->data[0]);

}

void print_bool(json_t *json_ttring, int i)
{
    print_ntab(i);
    printf("\"%s\": %s\n", json_ttring->id, json_ttring->data[0]);

}

void print_int(json_t *json_ttring, int i)
{
    int *nbr = json_ttring->data[0];

    print_ntab(i);
    printf("\"%s\": %d\n", json_ttring->id, *nbr);

}

void print_float(json_t *json_ttring, int i)
{
    float *nbr = json_ttring->data[0];

    print_ntab(i);
    printf("\"%s\": %f\n", json_ttring->id, *nbr);

}

void print_array(json_t *json_data, int tab)
{
    json_t *cur;
    void **data = json_data->data;

    print_ntab(tab);
    printf("%s:\n", json_data->id);
    print_ntab(tab);
    write(1, "[\n", 2);
    for (int i = 0; data[i]; i++) {
        cur = data[i];
        if (cur->type == JSONObject)
            print_obj(cur, tab + 1);
    }
    print_ntab(tab);
    write(1, "]\n", 2);
}

void print_obj(json_t *json_data, int tab)
{
    json_t *cur;
    void **data = json_data->data;

    print_ntab(tab);
    printf("%s:\n", json_data->id);
    for (int i = 0; data[i] != NULL; i++) {
        cur = data[i];
        if (cur->type == JSONObject)
            print_obj(cur, tab + 1);
        if (cur->type == JSONstring)
            print_string(cur, tab + 1);
        if (cur->type == JSONBoolean)
            print_bool(cur, tab + 1);
        if (cur->type == JSONInteger)
            print_int(cur, tab + 1);
        if (cur->type == JSONFloat)
            print_float(cur, tab + 1);
        if (cur->type == JSONArray)
            print_array(cur, tab + 1);
    }
}

void print_js(json_t *json_data)
{
    print_obj(json_data, 0);
}