#include <iostream>

using namespace std;

class AbstractProduct {
    public:
        AbstractProduct() = default;
        virtual ~AbstractProduct() = default;

        virtual void operate() = 0;
};

class ProductA : public AbstractProduct {
    public:
        ProductA() = default;
        ~ProductA() = default;

        void operate() {
            cout << "product A" << endl;
        }
};

class ProductB : public AbstractProduct {
    public:
        ProductB() = default;
        ~ProductB() = default;

        void operate() {
            cout << "product B" << endl;
        }
};

class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;
        virtual AbstractProduct *getProduct() = 0;
};

class ProductAFactory : public AbstractFactory {
public:
    AbstractProduct *getProduct() override
    {
        AbstractProduct *product = new ProductA();
        return product;
    }
};

class ProductBFactory : public AbstractFactory {
public:
    AbstractProduct *getProduct() override
    {
        AbstractProduct *product = new ProductB();
        return product;
    }
};

int main()
{
    AbstractFactory *factory = new ProductAFactory();
    AbstractProduct *product = factory->getProduct();
    product->operate();
    delete factory;
    delete product;

    factory = new ProductBFactory();
    product = factory->getProduct();
    product->operate();
    delete factory;
    delete product;

    return 0;
}
