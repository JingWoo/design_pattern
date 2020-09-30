#include "abstract_product.h"
#include <string.h>

static void AbstractProductOptOperate(AbstractProduct *product)
{
    printf("ProductOptOperate %s\n", (char *)product->pData);
}

static void AbstractProductOptDestroy(AbstractProduct **product)
{
    printf("AbstractProductOptDestroy\n");
    if ((*product)->pData != NULL) {
        free((*product)->pData);
        (*product)->pData = NULL;
    }
}

static AbstractProductOpt opts = {
    .operate = AbstractProductOptOperate,
    .destroy = AbstractProductOptDestroy,
};

void AbstractProductInit(AbstractProduct *product)
{
   (void)memset((void *)product, 0, sizeof(*product)); 
   product->pOpt = &opts;
}

