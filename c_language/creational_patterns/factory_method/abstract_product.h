#ifndef __FACTORY_METHOD_H
#define __FACTORY_METHOD_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _AbstractProduct AbstractProduct;
typedef struct _AbstractProductOpt AbstractProductOpt;

struct _AbstractProduct {
    AbstractProductOpt *pOpt;
    void *pData;
};

struct _AbstractProductOpt {
    void (*operate)(AbstractProduct *product);
};

void AbstractProductInit(AbstractProduct *product);

static inline void ProductOperate(AbstractProduct *product)
{
    product->pOpt->operate(product);
}

#ifdef __cplusplus
}
#endif

#endif
