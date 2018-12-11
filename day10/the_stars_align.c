#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

struct light
{
    int x;
    int y;
    int dx;
    int dy;
};

struct light lights[400];
int light_count = 0;

void disp_sky(int s)
{
    int maxy = 0, maxx = 0;
    int miny = INT_MAX, minx = INT_MAX;
    int x, y, i;
    for (i = 0; i < light_count; i++)
    {
        struct light l = lights[i];
        x = l.x + s * l.dx;
        y = l.y + s * l.dy;
        if (y > maxy)
            maxy = y;
        if (x > maxx)
            maxx = x;
        if (y < miny)
            miny = y;
        if (x < minx)
            minx = x;
    }
    int x_bound = maxx - minx + 1;
    int y_bound = maxy - miny + 1;
    char sky[y_bound][x_bound];
    memset(sky, '.', y_bound * x_bound);
    for (i = 0; i < 400; i++)
    {
        struct light l = lights[i];
        sky[l.y + s * l.dy - miny][l.x + s * l.dx - minx] = '#';
    }
    for (y = 0; y < y_bound; y++)
    {
        for (x = 0; x < x_bound; x++)
        {
            printf("%c", sky[y][x]);
        }
        printf("\n");
    }
    
    printf("Elapsed time: %d\n", s);
}

int main()
{
    /* FILE *input = fopen("test_input", "r"); */
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        perror("No input file found");
        return -1;
    }
    char buf[256];
    int i = 0;
    while (fgets(buf, 256, input))
    {
        struct light *l = &lights[i++];
        sscanf(buf, "position=<%d ,%d> velocity=<%d, %d>", &l->x, &l->y, &l->dx, &l->dy);
        light_count++;
    }

    int maxx, minx, maxy, miny;
    int x_bound, prev_xbound = -1;
    int y_bound, prev_ybound = -1;
    int disp_count = 5;
    int j;
    printf("Printing 5 likely candidates...\n");
    for (i = 0; i < 20000; i++)
    {
        maxy = maxx = 0;
        miny = minx = INT_MAX;
        for (j = 0; j < light_count; j++)
        {
            struct light l = lights[j];
            int x = l.x + i * l.dx;
            int y = l.y + i * l.dy;
            if (y > maxy)
                maxy = y;
            if (x > maxx)
                maxx = x;
            if (y < miny)
                miny = y;
            if (x < minx)
                minx = x;
        }
        x_bound = maxx - minx + 1;
        y_bound = maxy - miny + 1;
        if (prev_xbound != -1 && x_bound > prev_xbound && y_bound > prev_ybound)
        {
            disp_sky(i - 1);
            if (--disp_count == 0)
                break;
            getchar();
        }
        prev_xbound = x_bound;
        prev_ybound = y_bound;
    }
}
