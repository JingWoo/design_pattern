#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// product definition and realization
typedef struct product {
    int part_a;
    int part_b;
    int part_c;
    void (*set_part_a)(struct product *p, int value);
    void (*set_part_b)(struct product *p, int value);
    void (*set_part_c)(struct product *p, int value);
    void (*show_product)(struct product *p);
} product;

void set_part_a(struct product *p, int value)
{
    p->part_a = value;
}

void set_part_b(struct product *p, int value)
{
    p->part_b = value;
}

void set_part_c(struct product *p, int value)
{
    p->part_c = value;
}

void show_product(struct product *p)
{
    printf("part a: %d, part_b: %d, part_c: %d\n", p->part_a, p->part_b, p->part_c);
}

// abstract builder definition and realization
typedef struct builder {
    struct product *m_product;
    void (*create_product)(struct builder *b);
    void (*build_part_a)(struct builder *b);
    void (*build_part_b)(struct builder *b);
    void (*build_part_c)(struct builder *b);
    struct product *(*get_product)(struct builder *b);
} builder;

void create_product(struct builder *b)
{
    struct product *p = (struct product *)calloc(1, sizeof(struct product));
    assert(p != NULL);

    p->set_part_a = set_part_a;
    p->set_part_b = set_part_b;
    p->set_part_c = set_part_c;
    p->show_product = show_product;

    b->m_product = p;
}

struct product *get_product(struct builder *b)
{
    return b->m_product;
}

// concrete builder x
struct concrete_builder_x {
    struct builder super;
};

void build_part_x_a(struct builder *b)
{
    b->m_product->set_part_a(b->m_product, 1);
}

void build_part_x_b(struct builder *b)
{
    b->m_product->set_part_b(b->m_product, 1);
}

void build_part_x_c(struct builder *b)
{
    b->m_product->set_part_c(b->m_product, 1);
}

struct builder *concrete_builder_x_init()
{
    struct concrete_builder_x *c = (struct concrete_builder_x *)calloc(1, sizeof(struct concrete_builder_x));
    assert(c != NULL);

    c->super.create_product = create_product;
    c->super.build_part_a = build_part_x_a;
    c->super.build_part_b = build_part_x_b;
    c->super.build_part_c = build_part_x_c;
    c->super.get_product = get_product;

    return (struct builder *)c;
}

// concrete builder y
struct concrete_builder_y {
    struct builder super;
};

void build_part_y_a(struct builder *b)
{
    b->m_product->set_part_a(b->m_product, 2);
}

void build_part_y_b(struct builder *b)
{
    b->m_product->set_part_b(b->m_product, 2);
}

void build_part_y_c(struct builder *b)
{
    b->m_product->set_part_c(b->m_product, 2);
}

struct builder *concrete_builder_y_init()
{
    struct concrete_builder_y *c = (struct concrete_builder_y *)calloc(1, sizeof(struct concrete_builder_y));
    assert(c != NULL);

    c->super.create_product = create_product;
    c->super.build_part_a = build_part_y_a;
    c->super.build_part_b = build_part_y_b;
    c->super.build_part_c = build_part_y_c;
    c->super.get_product = get_product;

    return (struct builder *)c;
}

// director
struct director {
    struct builder *m_builder;
    void (*set_builder)(struct director *d, struct builder *b);
    struct product *(* construct)(struct director *d);
};

void set_builder(struct director *d, struct builder *b)
{
    d->m_builder = b;
}

struct product * construct(struct director *d)
{
    d->m_builder->create_product(d->m_builder);

    d->m_builder->build_part_a(d->m_builder);
    d->m_builder->build_part_b(d->m_builder);
    d->m_builder->build_part_c(d->m_builder);

    return d->m_builder->get_product(d->m_builder);
}

struct director *director_init()
{
    struct director *d = (struct director *)calloc(1, sizeof(struct director));
    assert(d != NULL);

    d->m_builder = NULL;
    d->set_builder = set_builder;
    d->construct = construct;

    return d;
}

int main()
{
    struct director *d = director_init();
    struct builder *x = concrete_builder_x_init();
    struct builder *y = concrete_builder_y_init();

    struct product *p = NULL;

    d->set_builder(d, x);
    p = d->construct(d);
    p->show_product(p);
    free(p);

    d->set_builder(d, y);
    p = d->construct(d);
    p->show_product(p);
    free(p);

    free(y);
    free(x);
    free(d);

    exit(EXIT_SUCCESS);
}
