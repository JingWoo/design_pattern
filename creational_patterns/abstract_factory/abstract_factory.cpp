#include <iostream>

using namespace std;

class AbstractProductA {
public:
    AbstractProductA() = default;
    virtual ~AbstractProductA() = default;

    virtual void operate() = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
    ConcreteProductA1() = default;
    ~ConcreteProductA1() = default;

    void operate()
    {
        cout << "concrete product A 1" << endl;
    }
};

class ConcreteProductA2 : public AbstractProductA {
public:
    ConcreteProductA2() = default;
    ~ConcreteProductA2() = default;

    void operate()
    {
        cout << "concrete product A 2" << endl;
    }
};

class AbstractProductB {
public:
    AbstractProductB() = default;
    virtual ~AbstractProductB() = default;

    virtual void operate() = 0;
};

class ConcreteProductB1 : public AbstractProductB {
public:
    ConcreteProductB1() = default;
    ~ConcreteProductB1() = default;

    void operate()
    {
        cout << "concrete product B 1" << endl;
    }
};

class ConcreteProductB2 : public AbstractProductB {
public:
    ConcreteProductB2() = default;
    ~ConcreteProductB2() = default;

    void operate()
    {
        cout << "concrete product B 2" << endl;
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual AbstractProductA *getProductA() = 0;
    virtual AbstractProductB *getProductB() = 0;
};

class ConcreteNFactory : public AbstractFactory {
public:
    AbstractProductA *getProductA() override
    {
        AbstractProductA *product = new ConcreteProductA1();
        return product;
    }
    AbstractProductB *getProductB() override
    {
        AbstractProductB *product = new ConcreteProductB1();
        return product;
    }
};

class ConcreteMFactory : public AbstractFactory {
public:
    AbstractProductA *getProductA() override
    {
        AbstractProductA *product = new ConcreteProductA2();
        return product;
    }
    AbstractProductB *getProductB() override
    {
        AbstractProductB *product = new ConcreteProductB2();
        return product;
    }
};

int main()
{
    AbstractFactory *factory = new ConcreteNFactory();
    AbstractProductA *productA = factory->getProductA();
    AbstractProductB *productB = factory->getProductB();
    productA->operate();
    productB->operate();
    delete productA;
    delete productB;
    delete factory;

    factory = new ConcreteMFactory();
    productA = factory->getProductA();
    productB = factory->getProductB();
    productA->operate();
    productB->operate();
    delete productA;
    delete productB;
    delete factory;

    return 0;
}
