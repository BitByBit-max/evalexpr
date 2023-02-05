#include "token_stack.h"

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

struct token_stack *token_stack_push(struct token_stack *s, int e,
                                     enum type_t type)
{
    struct token_stack *news = malloc(sizeof(struct token_stack) * 1);
    if (!news)
    {
        return s;
    }
    news->type = type;
    news->data = e;
    news->next = s;
    return news;
}

struct token_stack *token_stack_pop(struct token_stack *s)
{
    if (!s)
    {
        return s;
    }
    struct token_stack *new = s->next;
    free(s);
    return new;
}

int token_stack_data_peek(struct token_stack *s)
{
    return s->data;
}

int token_stack_type_peek(struct token_stack *s)
{
    return s->type;
}

void token_stack_free(struct token_stack *t)
{
    while (t)
    {
        t = token_stack_pop(t);
    }
}
