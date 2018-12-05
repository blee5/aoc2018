#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
 * Remove part of a string.
 * Specifically, removes [start, end)
 */
int remidx(char *s, size_t start, size_t end)
{
    /* Add 1 to copy the null terminator as well */
    memmove(&s[start], &s[end], strlen(s) + 1 - end); 
}

int main()
{
    FILE *input = fopen("input", "r");

    size_t len = 200;
    char *buf = malloc(len);
    int i = 0;
    for (;;)
    {
        int c = fgetc(input);
        if (c == EOF || c == '\n')
        {
            break;
        }
        buf[i++] = c;
        if (i >= len)
        {
            len *= 2;
            buf = realloc(buf, len);
        }
    }
    buf[i] = 0;
    len = strlen(buf);
    i = 0;
    while (i < len)
    {
        if (abs(buf[i] - buf[i + 1]) == abs('A' - 'a'))
        {
            memmove(&buf[i], &buf[i + 2], len + 1 - (i + 2));
            i -= 2;
            if (i < 0)
                i = 0;
            len -= 2;
        }
        else
        {
            i++;
        }
    }
    printf("Part 1 Answer:\n%ld\n", strlen(buf));
}
