#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Uses a circular doubly linked list
 *
 * prob leaks memory like crazy but who cares about that
 */

struct node
{
    long value;
    struct node *next;
    struct node *prev;
};

struct node *insert(struct node *n, long value)
{
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = n;
    new_node->prev = n->prev;
    new_node->prev->next = new_node;
    n->prev = new_node;
    return new_node;
};

long pop(struct node *n)
{
    long temp = n->value;
    n->prev->next = n->next;
    n->next->prev = n->prev;
    free(n);
    return temp;
}

long marble_game(long p_count, long f_marble)
{
    struct node z = {0, &z, &z};
    struct node *cur_marble = &z;
    long *scores = calloc(p_count, sizeof(long *));
    int cur_p = -1;

    long i, m;
    for (m = 1; m < f_marble + 1; m++)
    {
        cur_p = (cur_p + 1) % p_count;
        if (m % 23 == 0)
        {
            for (i = 0; i < 7; i++)
            {
                cur_marble = cur_marble->prev;
            }
            cur_marble = cur_marble->next;
            scores[cur_p] += m + pop(cur_marble->prev);
        }
        else
        {
            cur_marble = cur_marble->next->next;
            cur_marble = insert(cur_marble, m);
        }
    }

    long max = 0;
    for (i = 0; i < p_count; i++)
    {
        if (scores[i] > max)
            max = scores[i];
    }
    return max;
}

long main()
{
    int players = 419;
    int last_marble = 72164;

    printf("Part 1 Answer:\n%ld\n", marble_game(players, last_marble));
    printf("Part 2 Answer:\n%ld\n", marble_game(players, last_marble * 100));
}
