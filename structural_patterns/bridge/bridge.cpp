#include <iostream>

using namespace std;

class Implementor {
public:
    Implementor() = default;
    virtual ~Implementor() = default;
    virtual void operation() = 0;
};

class ConcreteImplementorA : public Implementor {
public:
    ConcreteImplementorA() = default;
    virtual ~ConcreteImplementorA() = default;

    void operation() override
    {
        std::cout << "ConcreteImplementorA" << std::endl;
    }
};

class ConcreteImplementorB : public Implementor {
public:
    ConcreteImplementorB() = default;
    virtual ~ConcreteImplementorB() = default;

    void operation() override
    {
        std::cout << "ConcreteImplementorB" << std::endl;
    }
};

class Abstraction {
public:
    Abstraction() = default;
    virtual ~Abstraction() = default;

    void setImplementor(Implementor *implementor)
    {
        this->m_implementor = implementor;
    }
    virtual void operation()
    {
        m_implementor->operation();
    }

protected:
    Implementor *m_implementor;
};

class RedfindAbstractionA : public Abstraction {
public:
    RedfindAbstractionA() = default;
    virtual ~RedfindAbstractionA() = default;
    void operation() override
    {
        std::cout << "RedfindAbstractionA ";
        m_implementor->operation();
    }
};

class RedfindAbstractionB : public Abstraction {
public:
    RedfindAbstractionB() = default;
    virtual ~RedfindAbstractionB() = default;
    void operation() override
    {
        std::cout << "RedfindAbstractionB ";
        m_implementor->operation();
    }
};

int main()
{
    Implementor *implementor = new ConcreteImplementorA();
    Abstraction *abstraction = new RedfindAbstractionA();
    abstraction->setImplementor(implementor);
    abstraction->operation();

    delete implementor;
    delete abstraction;

    implementor = new ConcreteImplementorB();
    abstraction = new RedfindAbstractionB();
    abstraction->setImplementor(implementor);
    abstraction->operation();

    delete implementor;
    delete abstraction;

    implementor = new ConcreteImplementorA();
    abstraction = new RedfindAbstractionB();
    abstraction->setImplementor(implementor);
    abstraction->operation();

    delete implementor;
    delete abstraction;

    return 0;
}
