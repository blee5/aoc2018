#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int num_points = 0;

struct point {
    int x;
    int y;
};

int manhattan_distance(struct point a, struct point b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

struct point *get_closest(int x, int y, struct point *points)
{
    struct point target = {x, y};
    struct point *closest = NULL;
    char is_unique = 1;
    int i;
    for (i = 0; i < num_points; i++)
    {
        if (!closest || manhattan_distance(target, points[i]) < manhattan_distance(target, *closest))
        {
            is_unique = 1;
            closest = &points[i];
        }
        else if (manhattan_distance(target, points[i]) == manhattan_distance(target, *closest))
        {
            is_unique = 0;
        }
    }
    if (is_unique)
        return closest;
    else
        return NULL;
}

void get_bounds(struct point *points, int *x, int *y)
{
    int i;
    int max_x = 0, max_y = 0;
    for (i = 0; i < num_points; i++)
    {
        if (points[i].x > max_x)
        {
            max_x = points[i].x;
        }
        if (points[i].y > max_y)
        {
            max_y = points[i].y;
        }
    }
    *x = max_x;
    *y = max_y;
}

int main()
{
    FILE *input = fopen("input", "r");
    char buf[256];
    int i = 0;
    while (fgets(buf, 256, input))
    {
        num_points++;
    }
    struct point *points = malloc(num_points * sizeof(struct point));
    rewind(input);
    while (fgets(buf, 256, input))
    {
        int x, y;
        sscanf(buf, "%d, %d", &x, &y);
        struct point c = {x, y};
        points[i++] = c;
    }

    int areas[num_points];
    memset(areas, 0, sizeof(int) * num_points);
    int x, y;
    int max_x, max_y;
    get_bounds(points, &max_x, &max_y);
    for (y = 0; y <= max_y; y++)
    {
        for (x = 0; x <= max_x; x++)
        {
            struct point *closest = get_closest(x, y, points);
            /* closest is null ifs equal distance to two or more points */
            if (closest)
            {
                int index = closest - points;
                if (x == 0 || x == max_x || y == 0 || y == max_y)
                {
                    /* Mark area as infinite */
                    areas[index] = -1;
                }
                else if (areas[index] >= 0)
                {
                    areas[index]++;
                }
            }
        }
    }

    int max_area = 0;
    for (i = 0; i < num_points; i++)
    {
        if (areas[i] > max_area)
        {
            max_area = areas[i];
        }
    }
    printf("Part 1 Answer:\n%d\n", max_area);

    int safe_area = 0;
    /*
     * BUG:
     * Technically it's possible for a point outside the bounding box to be a safe zone,
     * even if the input is valid for part 1.
     * For example: (0, 0) (0, 5) (5, 0) (5, 5) (3, 3)
     */
    for (y = 0; y <= max_y; y++)
    {
        for (x = 0; x <= max_x; x++)
        {
            int sum_dist = 0;
            struct point target = {x, y};
            for (i = 0; i < num_points; i++)
            {
                sum_dist += manhattan_distance(target, points[i]);
            }
            if (sum_dist < 10000)
            {
                safe_area++;
            }
        }
    }
    printf("Part 2 Answer:\n%d\n", safe_area);
    return 0; 
}
