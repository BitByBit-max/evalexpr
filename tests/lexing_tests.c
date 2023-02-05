#include <criterion/criterion.h>

#include "../src/evalexpr.h"

Test(lexing, simple_sum)
{
    char *expr = "1 2 +";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 0);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 1);
    cr_assert_eq(tlist->head->next->type, INT_T);
    cr_assert_eq(tlist->head->next->data, 2);
    cr_assert_eq(tlist->head->next->next->type, SUM_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing, number_sum)
{
    char *expr = "100 2 +";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 0);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 100);
    cr_assert_eq(tlist->head->next->type, INT_T);
    cr_assert_eq(tlist->head->next->data, 2);
    cr_assert_eq(tlist->head->next->next->type, SUM_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing, spaces_sum)
{
    char *expr = " 100     2+  ";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 0);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 100);
    cr_assert_eq(tlist->head->next->type, INT_T);
    cr_assert_eq(tlist->head->next->data, 2);
    cr_assert_eq(tlist->head->next->next->type, SUM_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing, only_one_number)
{
    char *expr = "102";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 0);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 102);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing, simple_sum_newline)
{
    char *expr = "1 2 +\n";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 0);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 1);
    cr_assert_eq(tlist->head->next->type, INT_T);
    cr_assert_eq(tlist->head->next->data, 2);
    cr_assert_eq(tlist->head->next->next->type, SUM_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing_nrm, simple_sum)
{
    char *expr = "1+2";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 1);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 1);
    cr_assert_eq(tlist->head->next->type, SUM_T);
    cr_assert_eq(tlist->head->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->data, 2);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing_nrm, number_sum)
{
    char *expr = "100+ 2";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 1);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 100);
    cr_assert_eq(tlist->head->next->type, SUM_T);
    cr_assert_eq(tlist->head->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->data, 2);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing_nrm, spaces_sum)
{
    char *expr = " 100     +2 ";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 1);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 100);
    cr_assert_eq(tlist->head->next->type, SUM_T);
    cr_assert_eq(tlist->head->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->data, 2);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing_nrm, only_one_number)
{
    char *expr = "102";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 1);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 102);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing_nrm, simple_sum_newline)
{
    char *expr = "1+2\n";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 1);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, INT_T);
    cr_assert_eq(tlist->head->data, 1);
    cr_assert_eq(tlist->head->next->type, SUM_T);
    cr_assert_eq(tlist->head->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->data, 2);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing_nrm, par_sum_un_mul)
{
    char *expr = "(+1+2) * (-3+4)";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 1);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, LPAR_T);
    cr_assert_eq(tlist->head->next->type, INT_T);
    cr_assert_eq(tlist->head->next->data, 0);
    cr_assert_eq(tlist->head->next->next->type, UNP_T);
    cr_assert_eq(tlist->head->next->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->next->data, 1);
    cr_assert_eq(tlist->head->next->next->next->next->type, SUM_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->data, 2);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->type, RPAR_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->type,
                 MUL_T);
    cr_assert_eq(
        tlist->head->next->next->next->next->next->next->next->next->type,
        LPAR_T);
    cr_assert_eq(
        tlist->head->next->next->next->next->next->next->next->next->next->type,
        INT_T);
    cr_assert_eq(
        tlist->head->next->next->next->next->next->next->next->next->next->data,
        0);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->type,
                 UNM_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->type,
                 INT_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->data,
                 3);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->type,
                 SUM_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->next->type,
                 INT_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->next->data,
                 4);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->next->next->type,
                 RPAR_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}

Test(lexing_nrm, par_sub_un_mod_div)
{
    char *expr = "(+1/2) - (-3%4)";
    int err = 0;
    struct token_queue *tlist = lexing(expr, &err, 1);
    cr_assert_not_null(tlist->head);
    cr_assert_eq(tlist->head->type, LPAR_T);
    cr_assert_eq(tlist->head->next->type, INT_T);
    cr_assert_eq(tlist->head->next->data, 0);
    cr_assert_eq(tlist->head->next->next->type, UNP_T);
    cr_assert_eq(tlist->head->next->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->next->data, 1);
    cr_assert_eq(tlist->head->next->next->next->next->type, DIV_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->type, INT_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->data, 2);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->type, RPAR_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->type,
                 SUB_T);
    cr_assert_eq(
        tlist->head->next->next->next->next->next->next->next->next->type,
        LPAR_T);
    cr_assert_eq(
        tlist->head->next->next->next->next->next->next->next->next->next->type,
        INT_T);
    cr_assert_eq(
        tlist->head->next->next->next->next->next->next->next->next->next->data,
        0);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->type,
                 UNM_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->type,
                 INT_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->data,
                 3);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->type,
                 MOD_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->next->type,
                 INT_T);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->next->data,
                 4);
    cr_assert_eq(tlist->head->next->next->next->next->next->next->next->next
                     ->next->next->next->next->next->next->type,
                 RPAR_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
}
