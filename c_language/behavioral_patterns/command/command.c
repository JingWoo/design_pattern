#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>

struct config {
    char *name;
    int age;
};

void free_config(struct config *c)
{
    if (c == NULL) {
        return;
    }
    free(c->name);
    c->name = NULL;
    free(c);
}

/* Callback prototype to set a configuration item.
 * Must be implemented when adding a new configuration key.
 */
typedef int (*config_set_cb)(const char *key, const char *value,
                             struct config *conf, void *data);

/* Callback prototype to get a configuration item.
 * Must be implemented when adding a new configuration key.
 */
typedef int (*config_get_cb)(const char *key, char *value, int inlen,
                             struct config *conf, void *data);

/* Callback prototype to clear a configuration item.
 * Must be implemented when adding a new configuration key.
 */
typedef int (*config_clr_cb)(const char *key, struct config *conf, void *data);

struct handler {
    char *name;
    config_set_cb set;
    config_get_cb get;
    config_clr_cb clr;
};


//cold
//
//    The cold attribute on functions is used to inform the compiler that the
//    function is unlikely to be executed. The function is optimized for size
//    rather than speed and on many targets it is placed into a special subsection
//    of the text section so all cold functions appear close together,improving
//    code locality of non-cold parts of program. The paths leading to calls of
//    cold functions within code are marked as unlikely by the branch prediction
//    mechanism. It is thus useful to mark functions used to handle unlikely
//    conditions, such as perror, as cold to improve optimization of hot functions
//    that do call marked functions in rare occasions.

//hot
//
//    The hot attribute on a function is used to inform the compiler that the
//    function is a hot spot of the compiled program. The function is optimized
//    more aggressively and on many targets it is placed into a special subsection of
//    the text section so all hot functions appear close together, improving locality.

#ifndef __hot
# define __hot __attribute__((hot))
#endif

#define project_config_define(name)                                     \
    __hot static int set_config_##name(const char *, const char *,      \
                                       struct config *, void *);        \
    __hot static int get_config_##name(const char *, char *, int,       \
                                       struct config *, void *);        \
    __hot static int clr_config_##name(const char *, struct config *,   \
                                       void *);

project_config_define(name);
project_config_define(age);

static struct handler config_jump_table[] = {
    { "name",                      set_config_name,                 get_config_name,                 clr_config_name,               },
    { "age",                       set_config_age,                  get_config_age,                  clr_config_age,                },
};

static const size_t config_jump_table_size = sizeof(config_jump_table) / sizeof(struct handler);

struct handler *get_config(const char *key)
{
    size_t i;

    for (i = 0; i < config_jump_table_size; i++)
        if (!strncmp(config_jump_table[i].name, key, strlen(config_jump_table[i].name))) {
            return &config_jump_table[i];
        }

    return NULL;
}

bool config_value_empty(const char *value)
{
    if (value && strlen(value) > 0) {
        return false;
    }

    return true;
}

int set_config_string_item(char **conf_item, const char *value)
{
    char *new_value;

    if (config_value_empty(value)) {
        free(*conf_item);
        *conf_item = NULL;
        return 0;
    }

    new_value = strdup(value);
    if (!new_value) {
        printf("Failed to duplicate string \"%s\"", value);
        return -1;
    }

    free(*conf_item);
    *conf_item = new_value;
    return 0;
}

static int set_config_name(const char *key, const char *value,
                           struct config *conf, void *data)
{
    if (config_value_empty(value)) {
        return clr_config_name(key, conf, NULL);
    }

    return set_config_string_item(&conf->name, value);
}

#define strprint(str, inlen, ...)                                       \
    do {                                                                \
        if (str)                                                        \
            len = snprintf(str, inlen, ##__VA_ARGS__);                  \
        else                                                            \
            len = snprintf((char *){""}, 0, ##__VA_ARGS__);             \
        if (len < 0) {                                                  \
            fprintf(stderr, "failed to create string");                 \
            return -1;                                                  \
        };                                                              \
        fulllen += len;                                                 \
        if (inlen > 0) {                                                \
            if (str)                                                    \
                str += len;                                             \
            inlen -= len;                                               \
            if (inlen < 0)                                              \
                inlen = 0;                                              \
        }                                                               \
    } while (0);


static int get_config_name(const char *key, char *retv, int inlen,
                           struct config *config, void *data)
{
    int len;
    int fulllen = 0;

    if (!retv) {
        inlen = 0;
    } else {
        memset(retv, 0, inlen);
    }

    strprint(retv, inlen, "%s", config->name);

    return fulllen;
}

static int clr_config_name(const char *key, struct config *conf, void *data)
{
    if (conf->name) {
        free(conf->name);
        conf->name = NULL;
    }

    return 0;
}

int safe_int(const char *numstr, int *converted)
{
    char *err = NULL;
    signed long int sli;

    errno = 0;
    sli = strtol(numstr, &err, 0);
    if (errno == ERANGE && (sli == LONG_MAX || sli == LONG_MIN)) {
        return -ERANGE;
    }

    if (errno != 0 && sli == 0) {
        return -EINVAL;
    }

    if (err == numstr || *err != '\0') {
        return -EINVAL;
    }

    if (sli > INT_MAX || sli < INT_MIN) {
        return -ERANGE;
    }

    *converted = (int)sli;
    return 0;
}

static int set_config_age(const char *key, const char *value,
                          struct config *conf, void *data)
{
    int ret;
    int age = 0;

    if (config_value_empty(value)) {
        conf->age = 0;
        return 0;
    }

    ret = safe_int(value, &age);
    if (ret < 0) {
        return -1;
    }

    conf->age = age;

    return 0;
}

int get_conf_int(struct config *c, char *retv, int inlen, int v)
{
    int len;
    int fulllen = 0;

    if (!retv) {
        inlen = 0;
    } else {
        memset(retv, 0, inlen);
    }

    strprint(retv, inlen, "%d", v);

    return fulllen;
}

static int get_config_age(const char *key, char *retv,
                          int inlen, struct config *c,
                          void *data)
{
    return get_conf_int(c, retv, inlen, c->age);
}

static inline int clr_config_age(const char *key, struct config *c,
                                 void *data)
{
    c->age = 0;
    return 0;
}

// Refine function to set and get

int main()
{
    struct config *conf = (struct config *)calloc(1, sizeof(struct config));
    assert(conf != NULL);
    struct handler *name_handler = get_config("name");
    name_handler->set("name", "uriel", conf, NULL);

    struct handler *age_handler = get_config("age");
    age_handler->set("age", "25", conf, NULL);

    size_t namelen = name_handler->get("name", NULL, 0, conf, NULL);
    if (namelen <= 0) {
        exit(EXIT_FAILURE);
    }
    char *name = (char *)calloc(1, sizeof(namelen + 1));
    assert(name != 0);
    if (name_handler->get("name", name, namelen + 1, conf, NULL) != namelen) {
        exit(EXIT_FAILURE);
    }

    size_t agelen = age_handler->get("age", NULL, 0, conf, NULL);
    if (agelen <= 0) {
        exit(EXIT_FAILURE);
    }
    char *age = (char *)calloc(1, sizeof(agelen + 1));
    assert(age != 0);
    if (age_handler->get("age", age, agelen + 1, conf, NULL) != agelen) {
        exit(EXIT_FAILURE);
    }

    printf("name: %s, age: %s\n", name, age);

    free(name);
    free(age);
    free_config(conf);

    exit(EXIT_SUCCESS);
}
