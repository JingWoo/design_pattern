#include "concrete_product_b.h"
#include "abstract_product.h"
#include <string.h>

static void ConcreteProductBOperate(AbstractProduct *product)
{
    printf("ConcreteProductB %s\n", (char *)product->pData);
}

static AbstractProductOpt opts = {
    .operate = ConcreteProductBOperate,
};

void ConcreteProductBInit(ConcreteProductB *product)
{
    (void)memset((void *)product, 0, sizeof(ConcreteProductB));
    AbstractProductInit(&product->product);
    product->product.pOpt = &opts;
    product->product.pData = strdup("ConcreteProductB");
    product->product.pInstance = product;
}
