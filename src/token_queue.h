#ifndef TOKEN_QUEUE_H
#define TOKEN_QUEUE_H

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_type.h"

struct list
{
    int data;
    enum type_t type;
    struct list *next;
};

struct token_queue
{
    size_t size;
    struct list *head;
    struct list *tail;
};

struct token_queue *token_queue_init(void);
size_t token_queue_size(struct token_queue *token_queue);
void token_queue_push(struct token_queue *token_queue, int elt,
                      enum type_t type);
int token_queue_head_data(struct token_queue *token_queue);
enum type_t token_queue_head_type(struct token_queue *token_queue);
void token_queue_pop(struct token_queue *token_queue);
void token_queue_clear(struct token_queue *token_queue);
void token_queue_destroy(struct token_queue *token_queue);
int token_precedence(enum type_t type);
int token_assos(enum type_t type);

#endif /* !TOKEN_QUEUE_H */
