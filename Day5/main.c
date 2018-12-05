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

int collapse(char *polymer)
{
    size_t len = strlen(polymer);
    int i = 0;
    while (i < len)
    {
        if (abs(polymer[i] - polymer[i + 1]) == abs('A' - 'a'))
        {
            remidx(polymer, i, i + 2); 
            i--;
            if (i < 0)
                i = 0;
            len -= 2;
        }
        else
        {
            i++;
        }
    }
    return len;
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
    char *bufcopy = malloc(len);
    bufcopy = strcpy(bufcopy, buf);
    printf("Part 1 Answer:\n%d\n", collapse(bufcopy));

    int min_length;
    char c;
    for (c = 'A'; c <= 'Z'; c++)
    {
        int i = 0;
        len = strlen(buf);
        bufcopy = strcpy(bufcopy, buf);
        while (i < len)
        {
            if (bufcopy[i] == c || bufcopy[i] - 32 == c)
            {
                remidx(bufcopy, i, i + 1); 
                len--;
            }
            else
            {
                i++;
            }
        }
        int res = collapse(bufcopy);
        if (c == 'A' || res < min_length)
            min_length = res;
    }
    printf("Part 2 Answer:\n%d\n", min_length);
}
