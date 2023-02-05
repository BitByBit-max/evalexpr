#ifndef EVALEXPR_H
#define EVALEXPR_H

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_queue.h"
#include "token_stack.h"

char *reading();
struct token_queue *lexing(char *expr, int *err, int rpn);
int evaluation(struct token_queue *tlist, int *err);
struct token_queue *torpn(struct token_queue *tlist, int *err);

#endif /* !EVALEXPR_H */
