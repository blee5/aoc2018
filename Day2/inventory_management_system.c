#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define arr_size 256

/*
 * Count the number of different characters in two strings with equal length
 */
int count_dif(const char *a, const char *b)
{
    int len = strlen(a);
    int count = 0;
    int i;
    for (i = 0; i < len; i++)
    {
        if (a[i] != b[i])
            count++;
    }
    return count;
}

int main()
{
    FILE *input = fopen("input", "r");
    char codes[arr_size][256];
    memset(codes, 0, arr_size);
    char buf[256];
    char charmap[256];

    int rep_two_count = 0;
    int rep_three_count = 0;
    int i, j, k;
    j = 0;

    while (fgets(buf, 256, input))
    {
        buf[strlen(buf) - 1] = 0; // strip newline
        strcpy(codes[j++], buf);
        memset(charmap, 0, 256);
        for (i = 0; buf[i]; i++)
        {
            charmap[(unsigned char)buf[i]]++;
        }
        int found_two = 0;
        int found_three = 0;
        for (i = 0; i < 256; i++)
        {
            if (!found_two && charmap[i] == 2)
            {
                found_two = 1;
                rep_two_count++;
            }
            if (!found_three && charmap[i] == 3)
            {
                found_three = 1;
                rep_three_count++;
            }
        }
    }
    printf("Part 1 Answer:\n%d\n", rep_two_count * rep_three_count);
    for (i = 0; i < arr_size; i++)
    {
        for (j = i; j < arr_size; j++)
        {
            char *a = codes[i];
            char *b = codes[j];
            if (count_dif(a, b) == 1)
            {
                k = 0;
                while (a[k] == b[k])
                    k++;
                /* Remove differing character */
                memmove(&a[k], &a[k + 1], strlen(a) - k);
                printf("Part 2 Answer:\n%s\n", a);
                return 0;
            }
        }
    }
}
