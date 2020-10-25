#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_OBSERVER_NUMS 10
struct subject;

struct observer {
    struct subject *subject;
    void (*update)(struct observer *observer);
};

struct subject {
    struct observer observer[MAX_OBSERVER_NUMS];
    int state;

    int (*get_state)(struct subject *subject);
    void (*set_state)(struct subject *subject, int state);
    void (*notify_all_observers)(struct subject *subject);
    void (*attach)(struct subject *subject, struct observer *observer);
};

static int get_state(struct subject *subject)
{
    return subject->state;
}

static void set_state(struct subject *subject, int state)
{
    subject->state = state;
    subject->notify_all_observers(subject);
}

static void notify_all_observers(struct subject *subject)
{
    int i;

    for (i = 0; i < MAX_OBSERVER_NUMS; i++) {
        if (subject->observer[i].update != NULL) {
            subject->observer[i].update(&subject->observer[i]);
        }
    }
}

static void attach(struct subject *subject, struct observer *observer) 
{
    static int observer_num = 0;

    if (observer_num >= MAX_OBSERVER_NUMS) {
        return;
    }

    memcpy(&subject->observer[observer_num++], observer, sizeof(struct observer));
}

struct subject *subject_init()
{
    struct subject *subject = (struct subject *)calloc(1, sizeof(struct subject));
    assert(subject != NULL);
    subject->state = 0;
    subject->get_state = get_state;
    subject->set_state = set_state;
    subject->notify_all_observers = notify_all_observers;
    subject->attach = attach;

    return subject;
}

static void octal_observer_update(struct observer *observer)
{
    printf("octal oberver: %o\n", get_state(observer->subject));
}

static void decimal_observer_update(struct observer *observer)
{
    printf("decimal oberver: %d\n", get_state(observer->subject));
}

static void hexa_observer_update(struct observer *observer)
{
    printf("hexa oberver: %x\n", get_state(observer->subject));
}

struct observer *observer_init(struct subject *subject, void (*update)(struct observer *))
{
    struct observer *observer = (struct observer *)calloc(1, sizeof(struct observer));
    assert(observer != NULL);
    observer->subject = subject;
    observer->update = update;

    return observer;
}

int main()
{
    struct subject *subject = subject_init();
    struct observer *octal_observer = observer_init(subject, octal_observer_update);
    struct observer *decimal_observer = observer_init(subject, decimal_observer_update);
    struct observer *hexa_observer = observer_init(subject, hexa_observer_update);

    subject->attach(subject, decimal_observer);
    subject->attach(subject, octal_observer);
    subject->attach(subject, hexa_observer);

    printf("State 1 ......\n");
    subject->set_state(subject, 1);
    printf("State 2 ......\n");
    subject->set_state(subject, 2);

    free(hexa_observer);
    free(decimal_observer);
    free(octal_observer);
    free(subject);

    exit(EXIT_SUCCESS);
}
