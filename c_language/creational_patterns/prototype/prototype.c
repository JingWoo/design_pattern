#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct module {
    int id;
    void *buffer;
    size_t buffer_size;
    struct module *(*clone)(struct module *m);
    void (*show)(struct module *m);
    void (*destroy)(struct module *mod);
} module;

static void show(struct module *m)
{
    printf("%s\n", (char *)m->buffer);
}

static void destroy(struct module *mod)
{
    free(mod->buffer);
    mod->buffer = NULL;
}

static struct module *module_clone(struct module *m)
{
    struct module *new_module = (struct module *)calloc(1, sizeof(struct module));
    assert(new_module != NULL);
    (void)memcpy(new_module, m, sizeof(struct module));
    new_module->buffer = (void *)strdup((char *)m->buffer);

    return new_module;
}

static struct module module_a = {
    .id = 0,
    .buffer = NULL,
    .buffer_size = 0,
    .clone = module_clone,
    .show = show,
    .destroy = destroy,
    };

int main()
{
    module_a.buffer = (void *)strdup("prototype design pattern in c");
    module_a.buffer_size = strlen((char *)(module_a.buffer)) + 1;
    module_a.show(&module_a);
    struct module *new_mod = module_a.clone(&module_a);
    new_mod->show(new_mod);
    new_mod->destroy(new_mod);
    module_a.destroy(&module_a);
    free(new_mod);

    exit(EXIT_SUCCESS);
}
