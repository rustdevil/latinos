#include "string.h"

int strlen(const char *s) {
    int n = 0;

    while (*s != '\0') {
        n++;
        s++;
    }

    return n;
}

char *strcat(char *dest, const char *src) {
    char *save = dest;
    dest += strlen(dest);

    while (*src != '\0') {
        *dest = *src;
        src++;
        dest++;
    }

    *dest = '\0';

    return save;
}
