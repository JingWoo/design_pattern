#ifndef __ABSTRACT_FACTORY_H
#define __ABSTRACT_FACTORY_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "abstract_product.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _AbstractFactory AbstractFactory;
typedef struct _AbstractFactoryOpt AbstractFactoryOpt;

struct _AbstractFactory {
    AbstractFactoryOpt *pOpt;
    void *pProduct;
    void *pInstance;
};

struct _AbstractFactoryOpt {
    AbstractProduct *(*create)(AbstractFactory *factory);
    void (*destroy)(AbstractFactory **factory);
};

void AbstractFactoryInit(AbstractFactory *factory);

static inline AbstractProduct *AbstructFactoryCreate(AbstractFactory *factory)
{
    factory->pOpt->create(factory);
}

static inline void AbstructFactoryDestroy(AbstractFactory **factory)
{
    (*factory)->pOpt->destroy(factory);
}

#ifdef __cplusplus
}
#endif

#endif
