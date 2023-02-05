#include <criterion/criterion.h>

#include "../src/evalexpr.h"

Test(evaluation, simple_sum)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 1, INT_T);
    token_queue_push(tlist, 2, INT_T);
    token_queue_push(tlist, 0, SUM_T);
    int err = 0;
    int res = evaluation(tlist, &err);
    cr_assert_eq(res, 3, "Expected 3. Got %d.", res);
    cr_assert_eq(err, 0, "Expected 0. Got %d.", err);
    token_queue_destroy(tlist);
}

Test(evaluation, simple_div)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 4, INT_T);
    token_queue_push(tlist, 2, INT_T);
    token_queue_push(tlist, 0, DIV_T);
    int err = 0;
    int res = evaluation(tlist, &err);
    cr_assert_eq(res, 2, "Expected 2. Got %d.", res);
    cr_assert_eq(err, 0, "Expected 0. Got %d.", err);
    token_queue_destroy(tlist);
}

Test(evaluation, simple_exp)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 2, INT_T);
    token_queue_push(tlist, 3, INT_T);
    token_queue_push(tlist, 0, EXP_T);
    int err = 0;
    int res = evaluation(tlist, &err);
    cr_assert_eq(res, 8, "Expected 8. Got %d.", res);
    cr_assert_eq(err, 0, "Expected 0. Got %d.", err);
    token_queue_destroy(tlist);
}

Test(evaluation, simple_mod)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 1, INT_T);
    token_queue_push(tlist, 2, INT_T);
    token_queue_push(tlist, 0, MOD_T);
    int err = 0;
    int res = evaluation(tlist, &err);
    cr_assert_eq(res, 1, "Expected 1. Got %d.", res);
    cr_assert_eq(err, 0, "Expected 0. Got %d.", err);
    token_queue_destroy(tlist);
}

Test(evaluation, slide_example)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 3, INT_T);
    token_queue_push(tlist, 4, INT_T);
    token_queue_push(tlist, 5, INT_T);
    token_queue_push(tlist, 0, MUL_T);
    token_queue_push(tlist, 3, INT_T);
    token_queue_push(tlist, 0, SUM_T);
    token_queue_push(tlist, 0, SUB_T);
    int err = 0;
    int res = evaluation(tlist, &err);
    cr_assert_eq(res, -20, "Expected -20. Got %d.", res);
    cr_assert_eq(err, 0, "Expected 0. Got %d.", err);
    token_queue_destroy(tlist);
}

Test(evaluation, complex_example)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 40, INT_T);
    token_queue_push(tlist, 2, INT_T);
    token_queue_push(tlist, 4, INT_T);
    token_queue_push(tlist, 0, EXP_T);
    token_queue_push(tlist, 4, INT_T);
    token_queue_push(tlist, 0, SUM_T);
    token_queue_push(tlist, 0, DIV_T);
    int err = 0;
    int res = evaluation(tlist, &err);
    cr_assert_eq(res, 2, "Expected 2. Got %d.", res);
    cr_assert_eq(err, 0, "Expected 0. Got %d.", err);
    token_queue_destroy(tlist);
}

Test(evaluation, err_exp)
{
    struct token_queue *tlist = token_queue_init();
    token_queue_push(tlist, 5, INT_T);
    token_queue_push(tlist, 2, INT_T);
    token_queue_push(tlist, 3, INT_T);
    token_queue_push(tlist, 0, SUB_T);
    token_queue_push(tlist, 0, EXP_T);
    int err = 0;
    evaluation(tlist, &err);
    cr_assert_eq(err, 3, "Expected err 3. Got %d.", err);
    token_queue_destroy(tlist);
}
