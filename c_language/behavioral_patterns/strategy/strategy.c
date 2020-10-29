#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct stragery {
    int (*operate)(int num1, int num2);
};

struct operation_add {
    struct stragery super;
};

static int operation_add_func(int num1, int num2)
{
    return num1 + num2;
}

static struct stragery *operation_add_init()
{
    struct operation_add *op = calloc(1, sizeof(struct operation_add));
    assert(op != NULL);
    op->super.operate = operation_add_func;

    return &op->super;
}

struct operation_sub {
    struct stragery super;
};

static int operation_sub_func(int num1, int num2)
{
    return num1 - num2;
}

static struct stragery *operation_sub_init()
{
    struct operation_sub *op = calloc(1, sizeof(struct operation_sub));
    assert(op != NULL);
    op->super.operate = operation_sub_func;
    return &op->super;
}

struct operation_mut {
    struct stragery super;
};

static int operation_mut_func(int num1, int num2)
{
    return num1 * num2;
}

static struct stragery *operation_mut_init()
{
    struct operation_mut *op = calloc(1, sizeof(struct operation_mut));
    assert(op != NULL);
    op->super.operate = operation_mut_func;
    return &op->super;
}

struct context {
    struct stragery *s;
    int (*execute_stratery)(struct context *ctx, int num1, int num2);
};

static int context_execute(struct context *ctx, int num1, int num2)
{
    return ctx->s->operate(num1, num2);
}

static void context_set_stratery(struct context *ctx, struct stragery *s)
{
    ctx->s = s;
}

static struct context *context_init()
{
    struct context *ctx = calloc(1, sizeof(struct context));
    assert(ctx != NULL);
    ctx->execute_stratery = context_execute;

    return ctx;
}

int main()
{
    struct context *ctx = context_init();
    struct stragery *s_add = operation_add_init();
    struct stragery *s_sub = operation_sub_init();
    struct stragery *s_mut = operation_mut_init();

    context_set_stratery(ctx, s_add);
    printf("do add operation: %d\n", ctx->execute_stratery(ctx, 1, 2));

    context_set_stratery(ctx, s_sub);
    printf("do add operation: %d\n", ctx->execute_stratery(ctx, 1, 2));

    context_set_stratery(ctx, s_mut);
    printf("do add operation: %d\n", ctx->execute_stratery(ctx, 1, 2));

    free(s_mut);
    free(s_sub);
    free(s_add);
    free(ctx);

    exit(EXIT_SUCCESS);
}
