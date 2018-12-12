#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define serial_number 8444

int cells[300][300];
int areas[300][300];

int power_level(int x, int y)
{
    x++; y++;
    return ((x + 10) * y + serial_number) * (x + 10) / 100 % 10 - 5;
}

int sum_area(int x, int y)
{
    /* Get sum from 1, 1 to x, y */
    int sum = power_level(x, y);
    if (x > 0)
        sum += areas[x - 1][y];
    if (y > 0)
        sum += areas[x][y - 1];
    if (x > 0 && y > 0)
        sum -= areas[x - 1][y - 1];
    return sum;
}

int sum_square(int x, int y, int size)
{
    int xmax = x + size - 1, ymax = y + size - 1;
    int sum = areas[xmax][ymax];
    if (x > 0)
        sum -= areas[x - 1][ymax];
    if (y > 0)
        sum -= areas[xmax][y - 1];
    if (x > 0 && y > 0)
        sum += areas[x - 1][y - 1];
    return sum;
}

int main()
{
    /* Note that the cell grid is 1-indexed. */
    int x, y;
    for (y = 0; y < 300; y++)
    {
        for (x = 0; x < 300; x++)
        {
            cells[x][y] = power_level(x, y);
        }
    }
    for (y = 0; y < 300; y++)
    {
        for (x = 0; x < 300; x++)
        {
            areas[x][y] = sum_area(x, y);
        }
    }
    int size = 3;
    int max_area = 0;
    printf("===PART1===\n");
    for (y = 0; y < 300 - size; y++)
    {
        for (x = 0; x < 300 - size; x++)
        {
            int area = sum_square(x, y, size);
            if (area > max_area)
            {
                max_area = area;
                printf("%d,%d has area %d\n", x + 1, y + 1, area);
            }
        }
    }

    printf("===PART2===\n");
    for (size = 1; size < 300; size++)
    {
        for (y = 0; y < 300 - size; y++)
        {
            for (x = 0; x < 300 - size; x++)
            {
                int area = sum_square(x, y, size);
                if (area > max_area)
                {
                    max_area = area;
                    printf("%d,%d,%d has area %d\n", x + 1, y + 1, size, area);
                }
            }
        }
    }
    return 0;
}
