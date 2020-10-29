#ifndef __UTIL_H
#define __UTIL_H
#include <stdlib.h>

#define define_cleaner_function(type, cleaner)           \
    static inline void cleaner##_function(type *ptr) \
    {                                                \
        if (*ptr)                                \
            cleaner(*ptr);                   \
    }
#define __auto_cleanup(cleaner) __attribute__((__cleanup__(cleaner##_function)))
static inline void ptr_free_function(void *p)
{
    free(*(void**)p);
}
#define __auto_free __auto_cleanup(ptr_free)

#define move_ptr(ptr)                                 \
    ({                                            \
        typeof(ptr) moved_ptr = (ptr);        \
        (ptr) = NULL;                         \
        moved_ptr;                            \
    })

#endif
