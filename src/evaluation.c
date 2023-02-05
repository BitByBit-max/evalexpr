#include "evalexpr.h"

int expo(int a, int b)
{
    int res = 1;
    for (int i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}

int evaluation(struct token_queue *tlist, int *err)
{
    struct token_stack *stack = NULL;
    while (tlist && tlist->head)
    {
        if (tlist->head->type == INT_T)
        {
            stack = token_stack_push(stack, tlist->head->data, INT_T);
            token_queue_pop(tlist);
            continue;
        }
        if (!stack || !stack->next)
        {
            *err = 2;
            fprintf(stderr, "syntax err");
            token_stack_free(stack);
            return 0;
        }
        int b = stack->data;
        stack = token_stack_pop(stack);
        int a = stack->data;
        stack = token_stack_pop(stack);
        int res = 0;
        switch (tlist->head->type)
        {
        case SUM_T:
        /* FALLTHROUGH */
        case UNP_T:
            res = a + b;
            break;
        case SUB_T:
        /* FALLTHROUGH */
        case UNM_T:
            res = a - b;
            break;
        case MUL_T:
            res = a * b;
            break;
        case DIV_T:
            if (b == 0)
            {
                *err = 3;
                fprintf(stderr, "arithmetical err");
                token_stack_free(stack);
                return 0;
            }
            res = a / b;
            break;
        case MOD_T:
            if (b == 0)
            {
                *err = 3;
                fprintf(stderr, "arithmetical err");
                token_stack_free(stack);
                return 0;
            }
            res = a % b;
            break;
        case EXP_T:
            if (b < 0)
            {
                *err = 3;
                fprintf(stderr, "arithmetical err");
                token_stack_free(stack);
                return 0;
            }
            res = expo(a, b);
            break;
        default:
            *err = 2;
            fprintf(stderr, "syntax err");
            token_stack_free(stack);
            return 0;
        }
        stack = token_stack_push(stack, res, INT_T);
        token_queue_pop(tlist);
    }
    if (!stack)
    {
        exit(0);
    }
    if (stack->next)
    {
        *err = 2;
        fprintf(stderr, "syntax err");
    }
    int res = stack->data;
    token_stack_free(stack);
    return res;
}
