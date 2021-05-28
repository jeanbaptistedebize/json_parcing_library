#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *fill_buffe_from_file(char *argv)
{
    int file = 0;
    char *buffer;
    struct stat buf;

    stat(argv, &buf);
    buffer = malloc(buf.st_size + 2);
    file = open(argv, O_RDONLY);
    if (file == -1) {
        free(buffer);
        return NULL;
    }
    read(file, buffer, buf.st_size);
    buffer[buf.st_size] = '\0';
    close(file);
    return buffer;
}