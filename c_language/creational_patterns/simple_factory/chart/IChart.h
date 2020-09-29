#ifndef __ICHART_H
#define __ICHART_H

typedef struct _IChart IChart;

struct _IChart {
    // Implements the interface. actual type pointer
    void *instance;
    // Business logic interface, agreed on specific operations
    void (*display)();
    /* ... */

    // Release the instance corresponding to the interface
    void (*destroy)(IChart **chart);
};
#endif
