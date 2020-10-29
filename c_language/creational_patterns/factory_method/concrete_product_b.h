#ifndef __CONCRETE_PRODUCT_B_H
#define __CONCRETE_PRODUCT_B_H
#include "abstract_product.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ConcreteProductB {
    AbstractProduct product;
} ConcreteProductB;

void ConcreteProductBInit(ConcreteProductB *product);

#ifdef __cplusplus
}
#endif

#endif /* __CONCRETE_PRODUCT_B_H */
