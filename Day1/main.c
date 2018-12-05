#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int freq = 0;
    FILE *input = fopen("input", "r");
    char buf[256];
    while (fgets(buf, 256, input))
    {
        freq += atoi(buf);
    }
    printf("Part 1 Answer:\n%d\n", freq);

    /*
     * Reset for part 2
     */
    rewind(input);
    freq = 0;
    int hist_size = 256; 
    int *freq_history = calloc(hist_size, sizeof(int));
    int freq_index = 0;
    int i;
    while (1)
    {
        if (fgets(buf, 256, input))
        {
            freq += atoi(buf);
            for (i = 0; i < freq_index; i++)
            {
                if (freq_history[i] == freq)
                {
                    printf("Part 2 Answer:\n%d\n", freq);
                    return 0;
                }
            }
            freq_history[freq_index++] = freq;
            if (freq_index >= hist_size)
            {
                hist_size *= 2;
                freq_history = realloc(freq_history, hist_size * sizeof(int));
            }
        }
        else
            rewind(input);
    }
    return 0;
}
