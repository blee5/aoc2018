#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct rule
{
    char before[5];
    char after;
};

void pad(char *pots)
{
    char *new = calloc(strlen(pots) + 11, 1);
    new = strcat(new, ".....");
    new = strcat(new, pots);
    new = strcat(new, ".....");
    strcpy(pots, new);
}

int strip(char *pots)
{
    // Returns the number of pots stripped from the beginning
    size_t i;
    size_t len = strlen(pots);
    for (i = 0; i < 50000; i++)
    {
        if (pots[len - 1 - i] != '.')
        {
            break;
        }
    }
    memset(pots + len - i, 0, i);
    len -= i;

    for (i = 0; i < 500000; i++)
    {
        if (pots[i] != '.')
        {
            break;
        }
    }
    memmove(pots, pots + i, len);
    return i;
}

long sum_pots(char *pots, size_t zeroth)
{
    long sum = 0;
    size_t numpots = strlen(pots);
    size_t i;
    for (i = 0; i < numpots; i++)
    {
        if (pots[i] == '#')
        {
            sum += i - zeroth;
        }
    }
    return sum;
}

int main()
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        perror("No input file found");
        return -1;
    }
    char buf[65535];
    char pots[65535];
    fgets(buf, 65535, input);
    sscanf(buf, "initial state: %s", pots);
    
    struct rule rules[20];
    char before[5] = {0};
    char after;
    size_t rules_len = 0;
    while (fgets(buf, 65535, input))
    {
        if (buf[0])
        {
            sscanf(buf, "%s => %c", before, &after);
            if (*before && before[2] != after)
            {
                strcpy(rules[rules_len].before, before);
                rules[rules_len++].after = after;
            }
        }
    }

    size_t zeroth = 0, prev_zeroth;
    char temp[65535]; // :(
    size_t i, j;
    for (i = 0; i < 500000; i++)
    {
        prev_zeroth = zeroth;
        pad(pots); 
        strcpy(temp, pots);
        zeroth += 5;

        size_t pots_len = strlen(pots);
        for (j = 0; j < pots_len - 5; j++)
        {
            struct rule r;
            size_t k;
            for (k = 0; k < rules_len; k++)
            {
                r = rules[k];
                if (strncmp(pots + j, r.before, 5) == 0)
                {
                    temp[j + 2] = r.after;
                }
            }
        }
        zeroth -= strip(temp);
        strip(pots);

        /* Eventually the pattern converges, but is shifted to the right by one pot */
        if (strcmp(temp, pots) == 0)
        {
            i++;
            break;
        }

        strcpy(pots, temp);
        if (i == 19)
        {
            printf("Part 1 Answer:\n%ld\n", sum_pots(pots, zeroth));
        }
    }
    printf("Part 2 Answer:\n%ld\n", sum_pots(pots, zeroth + (zeroth - prev_zeroth) * (50000000000 - i)));
}
