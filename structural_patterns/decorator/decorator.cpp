#include <iostream>

using namespace std;

class Component {
public:
    Component() = default;
    virtual ~Component() = default;
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
    ConcreteComponent() = default;
    virtual ~ConcreteComponent() = default;
    void operation() override
    {
        std::cout << "ConcreteComponent" << std::endl;
    }
};

class Decorator : public Component {
public:
    Decorator() = default;
    virtual ~Decorator() = default;
    void SetComponent(Component *c)
    {
        this->m_component = c;
    }

    virtual void operation()
    {
        if (m_component != nullptr) {
            m_component->operation();
        }
    }

private:
    Component *m_component;
};

class ConcreteDecoratorA : public Decorator {
public:
    void operation() override
    {
        Decorator::operation();
        m_addState = "New State";
        std::cout << "ConcreteDecoratorB " << m_addState << std::endl;
    }

private:
    std::string m_addState;
};

class ConcreteDecoratorB : public Decorator {
public:
    void operation() override
    {
        Decorator::operation();
        m_addBehavior = "New Behavior";
        std::cout << "ConcreteDecoratorB " << m_addBehavior << std::endl;
    }

private:
    std::string m_addBehavior;
};

int main()
{
    Component *component = new ConcreteComponent();
    Decorator *decoator = new ConcreteDecoratorA();
    decoator->SetComponent(component);
    decoator->operation();
    delete decoator;

    decoator = new ConcreteDecoratorB();
    decoator->SetComponent(component);
    decoator->operation();
    delete decoator;

    delete component;

    return 0;
}
