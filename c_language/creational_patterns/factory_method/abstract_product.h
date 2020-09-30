#ifndef __ABSTRACT_PRODUCT_H
#define __ABSTRACT_PRODUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _AbstractProduct AbstractProduct;
typedef struct _AbstractProductOpt AbstractProductOpt;

struct _AbstractProduct {
    AbstractProductOpt *pOpt;
    void *pData;
    void *pInstance;
};

struct _AbstractProductOpt {
    void (*operate)(AbstractProduct *product);
    void (*destroy)(AbstractProduct **product);
};

void AbstractProductInit(AbstractProduct *product);

static inline void AbstractProductOperate(AbstractProduct *product)
{
    product->pOpt->operate(product);
}

static inline void AbstractProductDestroy(AbstractProduct **product)
{
    (*product)->pOpt->destroy(product);
}

#ifdef __cplusplus
}
#endif

#endif
