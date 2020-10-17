#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct shape {
    void (*draw)();
};

void rectangle_draw()
{
    printf("Draw a rectangle\n");
}

void square_draw()
{
    printf("Draw a square\n");
}

void circle_draw()
{
    printf("Draw a circle\n");
}

struct shape_maker {
    struct shape rectangle;
    struct shape square;
    struct shape circle;
};

void facade_design_pattern()
{
    struct shape rectangle;
    struct shape square;
    struct shape circle;
    struct shape_maker maker;

    rectangle.draw = rectangle_draw;
    maker.rectangle = rectangle;
    square.draw = square_draw;
    maker.square = square;
    circle.draw = circle_draw;
    maker.circle = circle;
    maker.rectangle.draw();
    maker.square.draw();
    maker.circle.draw();
}

int main()
{
    facade_design_pattern();
    exit(EXIT_SUCCESS);
}
