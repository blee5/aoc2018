#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define fabric_size 1024

int main()
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        perror("No input file found");
        return -1;
    }
    char buf[256];
    int fabric[fabric_size][fabric_size];
    memset(fabric, 0, sizeof(int[0][0]) * fabric_size * fabric_size);
    int i, j;
    int id, x, y, height, width;
    while (fgets(buf, 256, input))
    {
        sscanf(buf, "#%*d @ %d,%d: %dx%d", 
            &x, &y, &height, &width); 
        for (i = height; i > 0; i--)
        {
            for (j = width; j > 0; j--)
            {
                fabric[x + i][y + j]++;
            }
        }
    }
    int count = 0;
    for (x = 0; x < fabric_size; x++)
    {
        for (y = 0; y < fabric_size; y++)
        {
            if (fabric[x][y] > 1)
            {
                count++;
            }
        }
    }
    printf("Part1 Answer:\n%d\n", count);
    rewind(input);
    loop:
    while (fgets(buf, 256, input))
    {
        sscanf(buf, "#%d @ %d,%d: %dx%d", 
            &id, &x, &y, &height, &width); 
        for (i = height; i > 0; i--)
        {
            for (j = width; j > 0; j--)
            {
                if (fabric[x + i][y + j] != 1)
                {
                    goto loop; // :o
                }
            }
        }
        printf("Part 2 Answer:\n%d\n", id);
        return 0;
    }
    return 0;
}
