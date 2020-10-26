#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct department {
    struct department *next;
    char *name;
    int (*callback)(int request);
    void (*set_next_department)(struct department *current, struct department *next);
    void (*destroy)(struct department *dep);
};

static void set_next_department(struct department *current, struct department *next)
{
    current->next = next;
}

static void destroy(struct department *dep)
{
    if (dep == NULL) {
        return;
    }
    free(dep->name);
    dep->name = NULL;
    free(dep);
}

struct department *department_init(const char *name, int (*callback)(int))
{
    struct department *department = (struct department *)calloc(1, sizeof(struct department));
    assert(department != NULL);
    department->name = strdup(name);
    department->callback = callback;
    department->set_next_department = set_next_department;
    department->destroy = destroy;

    return department;
}

int lower_department_handle_request(int request)
{
    if (request < 10) {
        printf("%s finish\n", __FUNCTION__);
        return 0;
    }

    printf("Can't handle by lower department\n");
    return -1;
}

int middle_department_handle_request(int request)
{
    if (request < 50) {
        printf("%s finish\n", __FUNCTION__);
        return 0;
    }

    printf("Can't handle by middle department\n");
    return -1;
}


int higher_department_handle_request(int request)
{
    if (request < 100) {
        printf("%s finish\n", __FUNCTION__);
        return 0;
    }

    printf("Can't handle by higher department\n");
    return -1;
}

int handle_request(struct department *dep, int request)
{
    if (dep->callback(request) == 0) {
        return 0;
    } else if (dep->next != NULL) {
        return handle_request(dep->next, request);
    } else {
        return -1;
    }
}

int main()
{
    struct department *lower = department_init("lower", lower_department_handle_request);
    struct department *middle = department_init("middle", middle_department_handle_request);
    struct department *higher = department_init("higher", higher_department_handle_request);

    lower->set_next_department(lower, middle);
    middle->set_next_department(middle, higher);

    handle_request(lower, 5);
    handle_request(lower, 25);
    handle_request(lower, 55);

    lower->destroy(lower);
    middle->destroy(middle);
    higher->destroy(higher);

    exit(EXIT_SUCCESS);
}
