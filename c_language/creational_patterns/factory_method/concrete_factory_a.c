#include "concrete_factory_a.h"
#include "abstract_factory.h"
#include "concrete_product_a.h"
#include <string.h>

static AbstractProduct *ConcreteFactoryAOptCreate(AbstractFactory *factory)
{
    printf("ConcreteFactoryACreate\n");
    ConcreteProductA *pa = (ConcreteProductA *)calloc(1, sizeof(ConcreteProductA));
    ConcreteProductAInit(pa);
    factory->pProduct = pa;
    return &pa->product;
}

static void ConcreteFactoryADestroy(ConcreteFactoryA **factory)
{
    assert(factory != NULL && *factory != NULL);
    ConcreteProductA *product = (*factory)->factory.pProduct;
    product->product.pOpt->destroy(&product);
}

static void ConcreteFactoryAOptDestroy(AbstractFactory **factory)
{
    printf("AbstractFactoryOptDestroy\n");
    assert(factory != NULL && *factory != NULL);
    ConcreteFactoryA *factorya = (ConcreteFactoryA *)(*factory)->pInstance;
    ConcreteFactoryADestroy(&factorya);
}

static AbstractFactoryOpt opts = {
    .create = ConcreteFactoryAOptCreate,
    .destroy = ConcreteFactoryAOptDestroy,

};

ConcreteFactoryA *ConcreteFactoryANew()
{
    ConcreteFactoryA *factory = (ConcreteFactoryA *)malloc(sizeof(ConcreteFactoryA));
    assert(factory != NULL);
    (void)memset((void *)factory, 0, sizeof(ConcreteFactoryA));
    AbstractFactoryInit(&factory->factory);
    factory->factory.pOpt = &opts;
    factory->factory.pInstance = factory;
    return factory;
}
