#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct guard {
    int id;
    int total_sleep;
    int sleep_record[60];
};

struct guard *guards;
int len = 0;

struct guard *add_guard(int id)
{
    len++;
    guards[len].id = id;
    return &guards[len];
}

struct guard *get_guard(int id)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (guards[i].id == id)
        {
            return &guards[i];
        }
    }
    return add_guard(id);
}

int cmpstr(const void* a, const void* b)
{
    const char* aa = *(const char**)a;
    const char* bb = *(const char**)b;
    return strcmp(aa,bb);
}

int main()
{
    FILE *input = fopen("input", "r");
    char buf[256];
    int id;
    struct guard *cur_guard;
    guards = calloc(300, sizeof(struct guard));
    int i;
    char **lines = calloc(5000, sizeof(void *));

    int linecount = 0;
    while (fgets(buf, 256, input))
    {
        lines[linecount] = calloc(256, sizeof(void *));
        strcpy(lines[linecount++], buf);
    }
    qsort(lines, linecount, sizeof(char *), cmpstr);

    for (i = 0; i < linecount; i++)
    {
        int sleep_begin;
        int sleep_end;
        if (strstr(lines[i], "begins shift"))
        {
            sscanf(lines[i], "[%*d-%*d-%*d %*d:%*d] Guard #%d", &id);
            cur_guard = get_guard(id);
        }
        else
        {
            sscanf(lines[i], "[%*d-%*d-%*d %*d:%d]", &sleep_begin);
            i++;
            sscanf(lines[i], "[%*d-%*d-%*d %*d:%d]", &sleep_end);
            int s;
            for (s = sleep_begin; s < sleep_end; s++)
            {
                cur_guard->sleep_record[s]++;
                cur_guard->total_sleep++;
            }
        }
    }
    struct guard *max_sleeper = NULL;
    for (i = 0; i < len; i++)
    {
        if (!max_sleeper || guards[i].total_sleep > max_sleeper->total_sleep)
        {
            max_sleeper = &guards[i];
        }
    }
    int max_sleep = 0;
    for (i = 0; i < 60; i++)
    {
        int *rec = max_sleeper->sleep_record;
        if (rec[i] > rec[max_sleep])
        {
            max_sleep = i;
        }
    }
    printf("Part 1 Answer:\n%d\n", max_sleeper->id * max_sleep);

    max_sleeper = NULL;
    int max_sleep_min = 0;
    int minute;
    for (minute = 0; minute < 60; minute++)
    {
        for (i = 0; i < len; i++)
        {
            if (!max_sleeper || guards[i].sleep_record[minute] > max_sleeper->sleep_record[max_sleep_min])
            {
                max_sleeper = &guards[i];
                max_sleep_min = minute;
            }
        }
    }
    printf("Part 2 Answer:\n%d\n", max_sleeper->id * max_sleep_min);
    return 0;
}
