#include "token_queue.h"

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

struct token_queue *token_queue_init(void)
{
    struct token_queue *f = malloc(sizeof(struct token_queue) * 1);
    f->head = NULL;
    f->tail = NULL;
    f->size = 0;
    return f;
}

void token_queue_clear(struct token_queue *token_queue)
{
    while (token_queue->head != NULL)
    {
        token_queue_pop(token_queue);
    }
}

void token_queue_destroy(struct token_queue *token_queue)
{
    token_queue_clear(token_queue);
    free(token_queue);
}

size_t token_queue_size(struct token_queue *token_queue)
{
    return token_queue->size;
}

void token_queue_push(struct token_queue *token_queue, int elt,
                      enum type_t type)
{
    struct list *l = malloc(sizeof(struct list) * 1);
    l->data = elt;
    l->type = type;
    l->next = NULL;
    if (token_queue->tail)
    {
        token_queue->tail->next = l;
        token_queue->tail = token_queue->tail->next;
    }
    else
    {
        token_queue->head = l;
        token_queue->tail = l;
    }
    token_queue->size += 1;
}

int token_queue_head_data(struct token_queue *token_queue)
{
    return token_queue->head->data;
}

enum type_t token_queue_head_type(struct token_queue *token_queue)
{
    return token_queue->head->type;
}

void token_queue_pop(struct token_queue *token_queue)
{
    if (token_queue->size > 0)
    {
        struct list *l = token_queue->head;
        token_queue->head = token_queue->head->next;
        free(l);
        token_queue->size -= 1;
    }
}

int token_precedence(enum type_t type)
{
    switch (type)
    {
    case RPAR_T:
    /* FALLTHROUGH */
    case LPAR_T:
        return 5;
    case UNP_T:
    /* FALLTHROUGH */
    case UNM_T:
        return 4;
    case EXP_T:
        return 3;
    case MUL_T:
    /* FALLTHROUGH */
    case DIV_T:
    /* FALLTHROUGH */
    case MOD_T:
        return 2;
    case SUM_T:
    /* FALLTHROUGH */
    case SUB_T:
        return 1;
    case INT_T:
        return 0;
    }
    return -1;
}

int token_assos(enum type_t type)
{
    switch (type)
    {
    case RPAR_T:
    /* FALLTHROUGH */
    case LPAR_T:
        return 0;
    case UNP_T:
    /* FALLTHROUGH */
    case UNM_T:
        return 1;
    case EXP_T:
        return 1;
    case MUL_T:
    /* FALLTHROUGH */
    case DIV_T:
    /* FALLTHROUGH */
    case MOD_T:
        return -1;
    case SUM_T:
    /* FALLTHROUGH */
    case SUB_T:
        return -1;
    case INT_T:
        return 0;
    }
    return -2;
}
