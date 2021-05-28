#include <stdlib.h>
#include "struct_json.h"

void free_obj(json_t *json_data);

void free_string(char **str)
{
    free(*str);
}

void free_array(json_t *json_data)
{
    void **data = json_data->data;

    for (int i = 0; data[i]; i++)
        free_obj(data[i]);
    free(data);
    free(json_data->id);
    free(json_data);
}

void free_data(json_t *data_string)
{
    free(data_string->id);
    free(data_string->data[0]);
    free(data_string->data);
    free(data_string);
}

void free_obj(json_t *json_data)
{
    json_t *cur;
    void **data = json_data->data;

    for (int i = 0; data[i] != NULL; i++) {
        cur = data[i];
        if (cur->type == JSONObject)
            free_obj(cur);
        else if (cur->type == JSONArray)
            free_array(cur);
        else
            free_data(cur);
    }
    free(data);
    free(json_data->id);
    free(json_data);
}

void free_js(json_t *json_data)
{
    free_obj(json_data);
}