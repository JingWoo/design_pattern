#ifndef __CONCRETE_FBCTORY_B_H
#define __CONCRETE_FBCTORY_B_H
#include "abstract_factory.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _ConcreteFactoryB {
    AbstractFactory factory;
} ConcreteFactoryB;

ConcreteFactoryB *ConcreteFactoryBNew();

#ifdef __cplusplus
}
#endif

#endif /* __CONCRETE_FBCTORY_B_H */
