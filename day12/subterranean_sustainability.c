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
    int pots[256];
    fgets(buf, 256, input);
    sscanf(buf, "initial state: %s", buf);

    while (fgets(buf, 256, input))
    {
        // Read file
    }
    printf("Part 2 Answer:\n%d\n", -1);
}
