#include "evalexpr.h"

struct token_queue *unary_check(struct token_queue *token_list)
{
    struct list *tlist = token_list->head;
    while (tlist && tlist->next)
    {
        if (tlist->type == RPAR_T
            && (tlist->next->type == SUM_T || tlist->next->type == SUB_T))
        {
            tlist = tlist->next->next;
            continue;
        }
        if (tlist->type == INT_T
            && (tlist->next->type == SUM_T || tlist->next->type == SUB_T))
        {
            tlist = tlist->next->next;
            continue;
        }
        if (tlist->type == SUM_T)
        {
            struct list *new = malloc(sizeof(struct list) * 1);
            new->data = 0;
            new->type = UNP_T;
            new->next = tlist->next;
            tlist->type = INT_T;
            tlist->next = new;
            token_list->size += 1;
        }
        if (tlist->type == SUB_T)
        {
            struct list *new = malloc(sizeof(struct list) * 1);
            new->data = 0;
            new->type = UNM_T;
            new->next = tlist->next;
            tlist->type = INT_T;
            tlist->next = new;
            token_list->size += 1;
        }
        tlist = tlist->next;
    }
    return token_list;
}

struct token_queue *lexing(char *expr, int *err, int rpn)
{
    struct token_queue *tlist = token_queue_init();
    int num = 0;
    int numadded = 0;
    for (int i = 0; expr[i] != '\0'; i++)
    {
        char c = expr[i];
        if ('0' <= c && c <= '9')
        {
            num = num * 10 + (c - '0');
            numadded = 1;
            continue;
        }
        else if (numadded)
        {
            token_queue_push(tlist, num, INT_T);
            num = 0;
            numadded = 0;
        }
        if (isspace(c))
        {
            continue;
        }
        switch (c)
        {
        case '+':
            token_queue_push(tlist, 0, SUM_T);
            break;
        case '-':
            token_queue_push(tlist, 0, SUB_T);
            break;
        case '*':
            token_queue_push(tlist, 0, MUL_T);
            break;
        case '/':
            token_queue_push(tlist, 0, DIV_T);
            break;
        case '%':
            token_queue_push(tlist, 0, MOD_T);
            break;
        case '^':
            token_queue_push(tlist, 0, EXP_T);
            break;
        case '(':
            if (rpn)
            {
                token_queue_push(tlist, 0, LPAR_T);
            }
            else
            {
                *err = 1;
                return tlist;
            }
            break;
        case ')':
            if (rpn)
            {
                token_queue_push(tlist, 0, RPAR_T);
            }
            else
            {
                *err = 1;
                return tlist;
            }
            break;
        default:
            *err = 1;
            return tlist;
            // errx(1, "invalid character");
        }
    }
    if (numadded)
    {
        token_queue_push(tlist, num, INT_T);
    }
    if (rpn && tlist)
    {
        tlist = unary_check(tlist);
    }
    return tlist;
}
