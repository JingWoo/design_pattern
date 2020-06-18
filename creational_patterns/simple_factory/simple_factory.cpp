#include <iostream>

using namespace std;

enum class ProductType : int {
    PRODUCTA,
    PRODUCTB
};

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

    void operate()
    {
        cout << "product A" << endl;
    }
};

class ProductB : public AbstractProduct {
public:
    ProductB() = default;
    ~ProductB() = default;

    void operate()
    {
        cout << "product B" << endl;
    }
};

class SimpleFactory {
public:
    SimpleFactory() = default;
    virtual ~SimpleFactory() = default;

    AbstractProduct *CreateProduct(ProductType type)
    {
        AbstractProduct *product = nullptr;
        switch (type) {
            case ProductType::PRODUCTA :
                product = new ProductA();
                break;
            case ProductType::PRODUCTB :
                product = new ProductB();
                break;
            default:
                cout << "Invalid product type" << endl;
                break;
        }

        return product;
    }
};

int main()
{
    SimpleFactory factory;
    AbstractProduct *product = factory.CreateProduct(ProductType::PRODUCTA);
    product->operate();
    delete product;

    product = factory.CreateProduct(ProductType::PRODUCTB);
    product->operate();
    delete product;

    return 0;
}
