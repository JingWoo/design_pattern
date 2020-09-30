#include "abstract_factory.h"
#include <string.h>
#include <assert.h>

static AbstractProduct *AbstractFactoryOptCreate(AbstractFactory *factory)
{
    printf("AbstractFactory\n");
}

static void AbstractFactoryOptDestroy(AbstractFactory **factory)
{
    printf("AbstractFactoryOptDestroy\n");
}

static AbstractFactoryOpt opts = {
    .create = AbstractFactoryOptCreate,
    .destroy = AbstractFactoryOptDestroy,
};

void AbstractFactoryInit(AbstractFactory *factory)
{
   (void)memset((void *)factory, 0, sizeof(*factory)); 
   factory->pOpt = &opts;
}
