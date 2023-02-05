#include "evalexpr.h"

char *reading()
{
    size_t sizexp = 0;
    size_t capacity = 2048;
    char *expr = malloc(sizeof(char) * 2049);
    char exbuf[2049];
    size_t r = fread(exbuf, sizeof(char), 2048, stdin);
    while (r != 0)
    {
        if (sizexp + r > capacity)
        {
            expr = realloc(expr, sizeof(char) * capacity * 2);
            if (!expr)
            {
                errx(4, "realloc failed");
            }
            capacity *= 2;
        }
        memcpy(expr + sizexp, exbuf, r);
        sizexp += r;
        r = fread(exbuf, sizeof(char), 2048, stdin);
    }
    expr[sizexp] = '\0';
    return expr;
}

int main(int argc, char *argv[])
{
    if (argc > 2) // other error (bad argument)
    {
        return 4;
    }
    // reading
    char *expr = reading();
    if (*expr == '\0') // no expression
    {
        free(expr);
        return 0;
    }
    int err = 0;
    struct token_queue *tlist = NULL;
    if (argc == 2)
    {
        if (!strcmp(argv[1], "-rpn"))
        {
            // lexing for rnp
            tlist = lexing(expr, &err, 0);
            free(expr);
            if (err)
            {
                token_queue_destroy(tlist);
                return err;
            }
        }
        else // other error (bad argument)
        {
            free(expr);
            return 4;
        }
    }
    else
    {
        // lexing for rpn
        tlist = lexing(expr, &err, 1);
        free(expr);
        if (err)
        {
            token_queue_destroy(tlist);
            return err;
        }
        struct token_queue *tlisttemp = torpn(tlist, &err); // syntactic
                                                            // analysis
        if (err)
        {
            token_queue_destroy(tlist);
            token_queue_destroy(tlisttemp);
            return err;
        }
        token_queue_destroy(tlist);
        tlist = tlisttemp;
    }
    // evaluation
    int res = evaluation(tlist, &err);
    token_queue_destroy(tlist);
    if (!err)
    {
        printf("%d\n", res);
    }
    return err;
}
