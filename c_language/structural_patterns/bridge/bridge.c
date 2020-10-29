#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Multi-dimensional independent changes without affecting each other
struct color_impl {
    void (*draw)(char *type);
};

struct red_shape {
    struct color_impl common;
};

struct green_shape {
    struct color_impl common;
};

static void draw_red_shape(char *type)
{
    printf("draw a red %s\n", type);
}

static void draw_green_shape(char *type)
{
    printf("draw a green %s\n", type);
}

struct color_impl *red_shape_init()
{
    struct red_shape *rs = (struct red_shape *)calloc(1, sizeof(struct red_shape));
    assert(rs != NULL);
    rs->common.draw = draw_red_shape;

    return (struct color_impl *)rs;
}

struct color_impl *green_shape_init()
{
    struct green_shape *gs = (struct green_shape *)calloc(1, sizeof(struct green_shape));
    assert(gs != NULL);
    gs->common.draw = draw_green_shape;

    return (struct color_impl *)gs;
}

struct shape {
    void (*draw)(struct shape *this);
    struct color_impl *impl;
};

struct square {
    struct shape super;
};

struct circle {
    struct shape super;
};

static void draw_square(struct shape *this)
{
    this->impl->draw("square");
}

static void draw_circle(struct shape *this)
{
    this->impl->draw("circle");
}

struct shape *square_init(struct color_impl *impl)
{
    struct square *s = (struct square *)calloc(1, sizeof(struct square));
    assert(s != NULL);
    s->super.draw = draw_square;
    s->super.impl = impl;

    return (struct shape *)s;
}

struct shape *circle_init(struct color_impl *impl)
{
    struct circle *c = (struct circle *)calloc(1, sizeof(struct circle));
    assert(c != NULL);
    c->super.draw = draw_circle;
    c->super.impl = impl;

    return (struct shape *)c;
}

int main()
{
    struct color_impl *red_impl = red_shape_init();
    struct color_impl *green_impl = green_shape_init();

    struct shape *red_square_shape = square_init(red_impl);
    red_square_shape->draw(red_square_shape);

    struct shape *green_circle_shape = circle_init(green_impl);
    green_circle_shape->draw(green_circle_shape);

    struct shape *green_square_shape = square_init(green_impl);
    green_square_shape->draw(green_square_shape);

    free(green_impl);
    free(red_impl);
    free(red_square_shape);
    free(green_circle_shape);
    free(green_square_shape);

    exit(EXIT_SUCCESS);
}
