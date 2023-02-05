#include <criterion/criterion.h>

#include "../src/evalexpr.h"

Test(torpn, simple_sum)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 1, INT_T);
    token_queue_push(tlist, 0, SUM_T);
    token_queue_push(tlist, 2, INT_T);
    int err = 0;
    struct token_queue *listrpn = torpn(tlist, &err);
    cr_assert_not_null(listrpn->head);
    cr_assert_eq(listrpn->head->type, INT_T);
    cr_assert_eq(listrpn->head->data, 1);
    cr_assert_eq(listrpn->head->next->type, INT_T);
    cr_assert_eq(listrpn->head->next->data, 2);
    cr_assert_eq(listrpn->head->next->next->type, SUM_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
    token_queue_destroy(listrpn);
}

Test(torpn, par_sum_mod)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 0, LPAR_T);
    token_queue_push(tlist, 45, INT_T);
    token_queue_push(tlist, 0, SUM_T);
    token_queue_push(tlist, 5, INT_T);
    token_queue_push(tlist, 0, RPAR_T);
    token_queue_push(tlist, 0, MOD_T);
    token_queue_push(tlist, 10, INT_T);
    int err = 0;
    struct token_queue *listrpn = torpn(tlist, &err);
    cr_assert_not_null(listrpn->head);
    cr_assert_eq(listrpn->head->type, INT_T);
    cr_assert_eq(listrpn->head->data, 45);
    cr_assert_eq(listrpn->head->next->type, INT_T);
    cr_assert_eq(listrpn->head->next->data, 5);
    cr_assert_eq(listrpn->head->next->next->type, SUM_T);
    cr_assert_eq(listrpn->head->next->next->next->type, INT_T);
    cr_assert_eq(listrpn->head->next->next->next->data, 10);
    cr_assert_eq(listrpn->head->next->next->next->next->type, MOD_T);
    cr_assert_eq(err, 0);
    token_queue_destroy(tlist);
    token_queue_destroy(listrpn);
}
