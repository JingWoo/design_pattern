#include "concrete_factory_b.h"
#include "abstract_factory.h"
#include "concrete_product_b.h"
#include <string.h>

static AbstractProduct *ConcreteFactoryBCreate(AbstractFactory *factory)
{
    printf("ConcreteFactoryBCreate\n");
    ConcreteProductB *pb = (ConcreteProductB *)calloc(1, sizeof(ConcreteProductB));
	ConcreteProductBInit(pb);
    factory->pProduct = pb;
	return &pb->product;
}

static AbstractFactoryOpt opts = {
    .create = ConcreteFactoryBCreate,
};

ConcreteFactoryB *ConcreteFactoryBNew()
{
    ConcreteFactoryB *factory = (ConcreteFactoryB *)malloc(sizeof(ConcreteFactoryB));
    assert(factory != NULL);
    (void)memset((void *)factory, 0, sizeof(ConcreteFactoryB));
    AbstractFactoryInit(&factory->factory);
    factory->factory.pOpt = &opts;

    return factory;
}
