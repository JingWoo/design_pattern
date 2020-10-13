#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct target {
    void (*request)(int parta, int partb);
} target;

void target_request(int parta, int partb)
{
    printf("%s\n", __FUNCTION__);
}

struct target *target_init()
{
    struct target *t = (struct target *)calloc(1, sizeof(struct target));
    assert(t != NULL);
    t->request = target_request;
    return t;
}

typedef struct adaptee {
    void (*request)(int para);
} adaptee;

void adaptee_request(int para)
{
    printf("%s\n", __FUNCTION__);
}

struct adaptee *adaptee_init()
{
    struct adaptee *t = (struct adaptee *)calloc(1, sizeof(struct adaptee));
    assert(t != NULL);
    t->request = adaptee_request;
    return t;
}

typedef struct adapter {
    struct target super;
} adapter;

void adapter_request(int parta, int partb)
{
    int para = parta + partb;
    struct adaptee *ad = adaptee_init();
    ad->request(para);
    free(ad);
}

struct target *adapter_init()
{
    struct adapter *adp = (struct adapter *)calloc(1, sizeof(struct adapter));
    assert(adp != NULL);
    adp->super.request = adapter_request;

    return (struct target *)adp;
}

int main()
{
    struct target *t = target_init();
    t->request(1, 2);

    struct target *adp = adapter_init();
    adp->request(1, 2);

    free(adp);
    free(t);

    exit(EXIT_SUCCESS);
}
