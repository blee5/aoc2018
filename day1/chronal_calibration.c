#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        perror("No input file found");
        return -1;
    }
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
    /* int offset = freqs[len - 1]; */
    /* int i; */
    /* int **modgroup = malloc(); */
    /* for (i; i < len; i++) */
    /* { */
        /* modgroup[freqs[i] % offset][] = ); */
    /* } */
}
