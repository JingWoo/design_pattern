#ifndef __CONCRETE_FACTORY_A_H
#define __CONCRETE_FACTORY_A_H
#include "abstract_factory.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _ConcreteFactoryA {
    AbstractFactory factory;
} ConcreteFactoryA;

ConcreteFactoryA *ConcreteFactoryANew();

#ifdef __cplusplus
}
#endif

#endif /* __CONCRETE_FACTORY_A_H */
