#include "concrete_product_a.h"
#include "abstract_product.h"
#include <string.h>

static void ConcreteProductAOperate(AbstractProduct *product)
{
    printf("ConcreteProductA %s\n", (char *)product->pData);
}

static void ConcreteProductADestroy(AbstractProduct **product)
{
    printf("ConcreteProductADestroy\n");

    if ((*product)->pData != NULL) {
        free((*product)->pData);
        (*product)->pData = NULL;
    }
}

static AbstractProductOpt opts = {
    .operate = ConcreteProductAOperate,
    .destroy = ConcreteProductADestroy,
};

void ConcreteProductAInit(ConcreteProductA *product)
{
    (void)memset((void *)product, 0, sizeof(ConcreteProductA));
    AbstractProductInit(&product->product);
    product->product.pOpt = &opts;
    product->product.pData = strdup("ConcreteProductA");
    product->product.pInstance = product;
}
