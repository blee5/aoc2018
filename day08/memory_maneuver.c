#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int *data;

void read_node(int *i, int *total, int *value)
{
    int child_count = data[(*i)++];
    int meta_count = data[(*i)++];

    int *child_values = calloc(child_count, sizeof(int));
    int j;
    for (j = 0; j < child_count; j++)
    {
        read_node(i, total, &child_values[j]);
    }

    for (j = 0; j < meta_count; j++)
    {
        *total += data[*i];
        if (child_count == 0)
            *value += data[*i];
        else
        {
            int child_idx = data[*i] - 1;
            if (child_idx < child_count)
                *value += child_values[child_idx];
        }
        (*i)++;
    }
}

int main()
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        perror("No input file found");
        return -1;
    }
    char *buf = malloc(40000);
    fgets(buf, 40000, input);

    int i = 0;
    data = malloc(40000 * sizeof(int));
    char *tok;
    while (tok = strsep(&buf, " "))
        data[i++] = atoi(tok);

    int p1 = 0, p2 = 0;
    i = 0;
    read_node(&i, &p1, &p2);
    printf("Part 1 Answer:\n%d\n", p1);
    printf("Part 2 Answer:\n%d\n", p2);
}
