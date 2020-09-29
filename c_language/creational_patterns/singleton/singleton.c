#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _Singleton Singleton;

struct _Singleton {
    void (*display)(Singleton *instance);
    void (*destroy)(Singleton **instance);
    void *pData;
};

static void display(Singleton *instance)
{
    printf("%s\n", (char *)instance->pData);
}

static void destroy(Singleton **instance)
{
    assert(instance != NULL && *instance != NULL);
    free((*instance)->pData);
    (*instance)->pData = NULL;
    free(*instance);
    *instance = NULL;
}

Singleton *get_instance()
{
    static Singleton *instance = NULL;

    if (instance == NULL) {
        // double lock
        instance = (Singleton *)calloc(1, sizeof(Singleton));
        assert(instance != NULL);
        instance->display = display;
        instance->destroy = destroy;
    }

    return instance;
}

int main()
{
    Singleton *instance = get_instance();
    instance->pData = strdup("Hello World");
    instance->display(instance);

    Singleton *other = get_instance();
    other->display(other);

    assert(instance == other);

    other->destroy(&other);
    assert(other == NULL);

    exit(EXIT_SUCCESS);
}

