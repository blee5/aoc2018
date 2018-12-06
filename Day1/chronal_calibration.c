#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int 

int main()
{
    int freq = 0;
    FILE *input = fopen("input", "r");
    char buf[256];
    int freqs[1100];
    int len = 0;
    while (fgets(buf, 256, input))
    {
        freq += atoi(buf);
        freqs[len++] = freq;
    }
    printf("Part 1 Answer:\n%d\n", freq);

    // TODO: Improved part2
    int offset = freqs[len - 1];
    int i;
    int **modgroup = malloc(2d array shit);
    for (i; i < len; i++)
    {
        modgroup[freqs[i] % offset][] = );
    }
}
