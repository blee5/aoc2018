#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct stack {
    char arr[50000];
    int count;
};

void push(struct stack *s, char c)
{
    s->arr[s->count++] = c;
}

char peek(struct stack *s)
{
    if (s->count == 0)
    {
        return 0;
    }
    return s->arr[s->count - 1];
}

char pop(struct stack *s)
{
    if (s->count == 0)
    {
        return 0;
    }
    return s->arr[--(s->count)];
}

int collapse(char *polymer, char ignore)
{
    struct stack s;
    s.count = 0;
    size_t len = strlen(polymer);
    int i = 0;
    for (i = 0; i < len; i++)
    {
        char c = polymer[i];
        if (c == ignore || c - 32 == ignore)
        {
            continue;
        }
        if (abs(c - peek(&s)) == abs('A' - 'a'))
        {
            pop(&s);
        }
        else
        {
            push(&s, c);
        }
    }
    return s.count;
}

int main()
{
    FILE *input = fopen("input", "r");

    size_t len = 200;
    char *buf = malloc(len);
    int i;
    int c = fgetc(input);
    for (i = 0; c != EOF && c != '\n'; c = fgetc(input))
    {
        buf[i++] = c;
        if (i >= len)
        {
            len *= 2;
            buf = realloc(buf, len);
        }
    }
    buf[i] = 0;

    printf("Part 1 Answer:\n%d\n", collapse(buf, 0));

    int min_length;
    for (c = 'A'; c <= 'Z'; c++)
    {
        int res = collapse(buf, c);
        if (c == 'A' || res < min_length)
            min_length = res;
    }
    printf("Part 2 Answer:\n%d\n", min_length);
}
