#include "abstract_product.h"

static void ProductOptOperate(AbstractProduct *product)
{
    printf("AbstractProduct %s", (char *)product->pData);
}

static AbstractProductOpt opts = {
    .operate = ProductOptOperate,
};

void AbstractProductInit(AbstractProduct *product)
{
   (void)memset((void *)product, 0, sizeof(*product)); 
   product->pOpt = &opts;
}
