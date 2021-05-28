/*
** EPITECH PROJECT, 2021
** json_parseur
** File description:
** fonc to parse string
*/

#include <string.h>
#include "my_error.h"
#include "struct_json.h"
#include <stdlib.h>

char *get_start_string_json(char *buffer, char c)
{
    while (*buffer == ' ' || *buffer == '\n')
        buffer++;
    if (*buffer != c && *buffer != '/')
        exit_error(ERROR_SYNTAX_JSON, EXIT_ERROR);
    return buffer;
}

void get_string_json(char **buffer, char **id)
{
    int i = 0;
    char temp[MAX_STRING_LEN];

    for (; (**buffer >= '*' && **buffer <= 'z') \
    || **buffer == ' '; i++, (*buffer)++)
        temp[i] = **buffer;
    temp[i] = '\0';
    if (**buffer != '"')
        exit_error(ERROR_SYNTAX_ID, EXIT_ERROR);
    (*buffer)++;
    *id = malloc(sizeof(char) * (i + 1));
    strcpy(*id, temp);
}
