#include "abstract_factory.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "abstract_product.h"
#include "concrete_factory_a.h"
#include "concrete_factory_b.h"
#include "concrete_product_a.h"
#include "concrete_product_b.h"

int main()
{
    AbstractProduct *product = NULL;
    ConcreteFactoryA *factoryA = NULL;
    ConcreteFactoryB *factoryB = NULL;

    factoryA = ConcreteFactoryANew();

    factoryB = ConcreteFactoryBNew();

    product = AbstructFactoryCreate(&factoryA->factory);
    AbstractProductOperate(product);
    ConcreteFactoryADestroy(factoryA);

    product = AbstructFactoryCreate(&factoryB->factory);
    AbstractProductOperate(product);
    // AbstractProductDestroy(&product);
    
}
