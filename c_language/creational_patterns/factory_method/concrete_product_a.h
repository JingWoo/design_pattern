#ifndef __CONCRETE_PRODUCT_A_H
#define __CONCRETE_PRODUCT_A_H
#include "abstract_product.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ConcreteProductA {
    AbstractProduct product;
} ConcreteProductA;

void ConcreteProductAInit(ConcreteProductA *product);

#ifdef __cplusplus
}
#endif

#endif /* __CONCRETE_PRODUCT_A_H */
