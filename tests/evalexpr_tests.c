#include <criterion/criterion.h>

#include "../src/tinyprintf.h"

Test(digit_count_test, basic)
{
    int actual = digit_count(424);
    int expected = 3;
    cr_assert_eq(actual, expected, "Expected %d. Got %d.", expected, actual);
}
