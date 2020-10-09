#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _AssembleHouse {
    char *m_floor;
    char *m_wall;
    char *m_roof;

    void (*setFloor)();
    void (*setWall)();
    void (*show)();
} AssembleHouse;

static AssembleHouse g_house;

static void setFloorA()
{
    free(g_house.m_floor);
    g_house.m_floor = strdup("style A");
}

static void setWallA()
{
    free(g_house.m_wall);
    g_house.m_wall = strdup("style A");
}

static void show()
{
    printf("Floor: %s, Wall: %s\n", g_house.m_floor, g_house.m_wall);
}

static void setFloorB()
{
    free(g_house.m_floor);
    g_house.m_floor = strdup("style B");
}

static void setWallB()
{
    free(g_house.m_wall);
    g_house.m_wall = strdup("style B");
}

int main()
{
    g_house.setFloor = setFloorA;
    g_house.setWall = setWallA;
    g_house.show = show;
    g_house.setFloor();
    g_house.setWall();
    g_house.show();

    exit(EXIT_SUCCESS);
}

