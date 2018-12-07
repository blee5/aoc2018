#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct step
{
    char status;
    char name;
    struct step **prereq_for;
};

struct step steps[26];

void add_dep(char name, char dep)
{
    int i;
    struct step *s = &steps[dep - 'A'];
    for (i = 0; s->prereq_for[i] != NULL; i++);
    s->prereq_for[i] = &steps[name - 'A'];
}

void run_step(struct step *s)
{
    int i;
    printf("%c", s->name);
}

int main()
{
    FILE *input = fopen("input", "r");
    if (input == NULL)
    {
        perror("No input file found");
        return -1;
    }
    char buf[256];
    int i;
    for (i = 0; i < 26; i++)
    {
        steps[i].name = 'A' + i;
        steps[i].status = -1;
        steps[i].prereq_for = calloc(sizeof(struct step *), 10);
    }
    while (fgets(buf, 256, input))
    {
        // Read file
        char name, depends;
        sscanf(buf, "Step %c must be finished before step %c can begin.", &depends, &name);
        steps[name - 'A'].status = 0;
        add_dep(name, depends);
    }

    struct step *start;
    for (i = 0; i < 26; i++)
    {
        if (steps[i].status != -1 && steps[i].prereq_for[0] == NULL)
        {
            start = &steps[i];
            break;
        }
    }
    printf("Part 1 Answer:\n");
    run_step(start);
    printf("\n");

    /* printf("Part 2 Answer:\n%d\n", -1); */
}
