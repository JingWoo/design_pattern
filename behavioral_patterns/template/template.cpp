#include <iostream>

using namespace std;

class AbstractClass {
    public:
        void TemplateMethod() {
            PrimitiveOperation1();
            PrimitiveOperation2();
            PrimitiveOperation3();
        }
        virtual void PrimitiveOperation1() = 0;
        virtual void PrimitiveOperation2() = 0;
        virtual void PrimitiveOperation3() = 0;
};

class ConcreteClassA : public AbstractClass {
    public:
        void PrimitiveOperation1() override {
            std::cout << "A PrimitiveOperation1" << std::endl;
        }
        void PrimitiveOperation2() override {
            std::cout << "A PrimitiveOperation2" << std::endl;
        }
        void PrimitiveOperation3() override {
            std::cout << "A PrimitiveOperation3" << std::endl;
        }
};

class ConcreteClassB : public AbstractClass {
    public:
        void PrimitiveOperation1() override {
            std::cout << "B PrimitiveOperation1" << std::endl;
        }
        void PrimitiveOperation2() override {
            std::cout << "B PrimitiveOperation2" << std::endl;
        }
        void PrimitiveOperation3() override {
            std::cout << "B PrimitiveOperation3" << std::endl;
        }
};

int main() {
    auto abstractA = new ConcreteClassA;
    abstractA->TemplateMethod();

    std::cout << std::endl;
    auto abstractB = new ConcreteClassB;
    abstractB->TemplateMethod();

    delete abstractA;
    delete abstractB;

    return 0;
}
