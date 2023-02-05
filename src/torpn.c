#include "evalexpr.h"

int isoperator(enum type_t type)
{
    switch (type)
    {
    case RPAR_T:
    /* FALLTHROUGH */
    case LPAR_T:
    /* FALLTHROUGH */
    case INT_T:
        return 0;
    case EXP_T:
    /* FALLTHROUGH */
    case MUL_T:
    /* FALLTHROUGH */
    case DIV_T:
    /* FALLTHROUGH */
    case MOD_T:
    /* FALLTHROUGH */
    case SUM_T:
    /* FALLTHROUGH */
    case SUB_T:
    /* FALLTHROUGH */
    case UNP_T:
    /* FALLTHROUGH */
    case UNM_T:
        return 1;
    default:
        return -1;
    }
}

struct token_queue *torpn(struct token_queue *tlist, int *err)
{
    struct token_queue *output = token_queue_init();
    struct token_stack *operator= NULL;
    while (tlist->head)
    {
        int token_data = tlist->head->data;
        enum type_t token_type = tlist->head->type;
        token_queue_pop(tlist);
        if (token_type == INT_T)
        {
            token_queue_push(output, token_data, INT_T);
        }
        else if (isoperator(token_type))
        {
            while (operator&& isoperator(token_stack_type_peek(operator))
                   && (token_precedence(token_type)
                           < token_precedence(token_stack_type_peek(operator))
                       || (token_precedence(token_type)
                               == token_precedence(
                                   token_stack_type_peek(operator))
                           && token_assos(token_type) == -1)))
            {
                token_queue_push(output, token_stack_data_peek(operator),
                                 token_stack_type_peek(operator));
                operator= token_stack_pop(operator);
            }
            operator= token_stack_push(operator, token_data, token_type);
        }
        else if (token_type == LPAR_T)
        {
            operator= token_stack_push(operator, 0, LPAR_T);
        }
        else if (token_type == RPAR_T)
        {
            while (operator&& token_stack_type_peek(operator) != LPAR_T)
            {
                token_queue_push(output, token_stack_data_peek(operator),
                                 token_stack_type_peek(operator));
                operator= token_stack_pop(operator);
            }
            if (!operator)
            {
                *err = 2;
                token_stack_free(operator);
                return output;
            }
            operator= token_stack_pop(operator);
        }
    }
    while (operator)
    {
        if (token_stack_type_peek(operator) == LPAR_T)
        {
            *err = 2;
            token_stack_free(operator);
            return output;
        }
        token_queue_push(output, token_stack_data_peek(operator),
                         token_stack_type_peek(operator));
        operator= token_stack_pop(operator);
    }
    return output;
}
