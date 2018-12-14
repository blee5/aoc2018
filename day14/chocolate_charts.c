#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define input 890691
#define input_length 6

int main()
{
    int arr_input[] = {8, 9, 0, 6, 9, 1};

    int rec_size = 2;
    int *recipes = calloc(rec_size, sizeof(int));
    recipes[0] = 3;
    recipes[1] = 7;
    int elf_1 = 0, elf_2 = 1;
    int rec_count = 2;
    int i = 0, j;
    for(;; i++)
    {
        if (rec_count + 2 >= rec_size)
        {
            rec_size *= 2;
            recipes = realloc(recipes, rec_size * sizeof(int));
        }
        int sum = recipes[elf_1] + recipes[elf_2];
        if (sum > 9)
            recipes[rec_count++] = 1;
        recipes[rec_count++] = sum % 10;
        elf_1 = (elf_1 + recipes[elf_1] + 1) % rec_count;
        elf_2 = (elf_2 + recipes[elf_2] + 1) % rec_count;

        if (i == input + 9)
        {
            printf("Part 1 Answer:\n");
            for (j = 0; j < 10; j++)
            {
                printf("%d", recipes[input + j]);
            }
            printf("\n");
        }

        if (rec_count > i + input_length)
        {
            char found = 1;
            for (j = 0; j < input_length; j++)
            {
                if (recipes[i + j] != arr_input[j])
                {
                    found = 0;
                    break;
                }
            }
            if (found)
            {
                printf("Part 2 Answer:\n%d\n", i);
                break;
            }
        }
    }
    free(recipes);
}
