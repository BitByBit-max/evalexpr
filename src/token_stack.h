#ifndef TOKEN_STACK_H
#define TOKEN_STACK_H

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_type.h"

struct token_stack
{
    int data;
    enum type_t type;
    struct token_stack *next;
};

struct token_stack *token_stack_push(struct token_stack *s, int e,
                                     enum type_t type);
struct token_stack *token_stack_pop(struct token_stack *s);
int token_stack_data_peek(struct token_stack *s);
void token_stack_free(struct token_stack *t);
int token_stack_type_peek(struct token_stack *s);

#endif /* !TOKEN_STACK_H */
