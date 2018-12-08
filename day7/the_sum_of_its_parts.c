#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_WORKERS 5

struct step
{
    char name;
    char is_done;
    struct step **prereq_for;
    struct step **prereq;
};

struct step *steps[26];
struct step **available;
struct step *seq[26];

void append(struct step **list, struct step *s)
{
    int i;
    for (i = 0; list[i]; i++);
    list[i] = s;
}

void del(struct step **list, struct step *s)
{
    int i = 0;
    while (list[i++] != s);
    i--;
    for (; i < 25; i++)
    {
        list[i] = list[i + 1];
    }
}

void add_step(char name)
{
    int index = name - 'A';
    if (steps[index] == NULL)
    {
        steps[index] = malloc(sizeof(struct step));
        steps[index]->name = name;
        steps[index]->is_done = 0;
        steps[index]->prereq_for = calloc(26, sizeof(struct step *));
        steps[index]->prereq = calloc(26, sizeof(struct step *));
    }
}

void add_dep(char name, char dep)
{
    append(steps[dep - 'A']->prereq_for, steps[name - 'A']);
    append(steps[name - 'A']->prereq, steps[dep - 'A']);
}

struct step *get_first()
{
    struct step *first = NULL;
    int i;
    for (i = 0; available[i]; i++)
    {
        if (!first || available[i]->name < first->name)
        {
            first = available[i];
        }
    }
    return first;
}

int prereq_met(struct step *s)
{
    int i;
    for (i = 0; s->prereq[i]; i++)
    {
        if (s->prereq[i]->is_done == 0)
        {
            return 0;
        }
    }
    return 1;
}

void run()
{
    while (available[0] != NULL)
    {
        struct step *s = get_first();
        int i;
        s->is_done = 1;
        for (i = 0; s->prereq_for[i]; i++)
        {
            if (prereq_met(s->prereq_for[i]))
            {
                append(available, s->prereq_for[i]);
            }
        }
        del(available, s);
        append(seq, s);
    }
}

/*
 * Part 2 
 */

struct worker
{
    struct step *task;
    int t;
};

struct worker workers[NUM_WORKERS];

struct worker *get_idle()
{
    int i;
    for (i = 0; i < NUM_WORKERS; i++)
    {
        if (workers[i].task == NULL)
        {
            return &workers[i];
        }
    }
    return NULL;
}

int run_workers()
{
    int total_t = 0;
    while (1)
    {
        int i;
        for (i = 0; i < NUM_WORKERS; i++)
        {
            if (--workers[i].t == 0)
            {
                workers[i].task->is_done = 1;
                int j;
                for (j = 0; workers[i].task->prereq_for[j]; j++)
                {
                    if (prereq_met(workers[i].task->prereq_for[j]))
                        append(available, workers[i].task->prereq_for[j]);
                }
                workers[i].task = NULL;
                workers[i].t = -1;
            }
        }
        while (available[0])
        {
            struct worker *w = get_idle();
            if (w == NULL)
                break;
            struct step *s = get_first();
            w->task = s;
            w->t = s->name - 'A' + 1 + 60;
            del(available, s);
        }

        /* If all the workers aren't doing anything, the job is done! */
        if (available[0] == NULL)
        {
            for (i = 0; i < NUM_WORKERS; i++)
            {
                if (workers[i].task != NULL)
                    break;
            }
            if (i == NUM_WORKERS)
                break;
        }
        total_t++;
    }
    return total_t;
}

/*
 * End Part 2
 */

int main()
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        perror("No input file found");
        return -1;
    }
    char buf[256];
    available = calloc(26, sizeof(struct step **));
    memset(available, 0, 10 * sizeof(struct step **));
    memset(steps, 0, 26 * sizeof(struct step **));
    memset(seq, 0, 26 * sizeof(struct step **));
    while (fgets(buf, 256, input))
    {
        // Read file
        char name, depends;
        sscanf(buf, "Step %c must be finished before step %c can begin.", &depends, &name);
        add_step(name);
        add_step(depends);
        add_dep(name, depends);
    }

    int i;
    for (i = 0; i < 26; i++)
    {
        if (steps[i] && steps[i]->prereq[0] == NULL)
        {
            append(available, steps[i]);
        }
    }
    printf("Part 1 Answer:\n");
    run();
    for (i = 0; seq[i]; i++)
    {
        printf("%c", seq[i]->name);
    }
    printf("\n");

    /* Reset for part 2 */
    for (i = 0; i < 26; i++)
    {
        if (steps[i] && steps[i]->prereq[0] == NULL)
        {
            append(available, steps[i]);
        }
        steps[i]->is_done = 0;
    }
    for (i = 0; i < NUM_WORKERS; i++)
    {
        workers[i].task = NULL;
        workers[i].t = -1;
    }
    printf("Part 2 Answer:\n%d\n", run_workers());
}
