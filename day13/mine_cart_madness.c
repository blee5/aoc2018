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
    while (fgets(buf, 256, input))
    {
        // Read file
    }

    printf("Part 1 Answer:\n%d\n", -1);
    printf("Part 2 Answer:\n%d\n", -1);
}
