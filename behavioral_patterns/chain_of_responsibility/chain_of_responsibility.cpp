#include <iostream>
#include <memory>

using namespace std;

class Handler {
public:
    Handler() = default;
    virtual ~Handler() = default;
    void SetSuccessor(std::shared_ptr<Handler> successor)
    {
        this->m_successor = successor;
    }

    virtual void handle(int request) = 0;

protected:
    std::shared_ptr<Handler> m_successor;
};

class ConcreteHandlerA : public Handler {
public:
    ConcreteHandlerA() = default;
    virtual ~ConcreteHandlerA() = default;

    void handle(int request) override
    {
        if (request == 1) {
            std::cout << "ConcreteHandlerA" << std::endl;
        } else {
            if (m_successor != nullptr) {
                m_successor->handle(request);
            } else {
                std::cout << "Cannot handle request" << std::endl;
            }
        }
    }
};

class ConcreteHandlerB : public Handler {
public:
    ConcreteHandlerB() = default;
    virtual ~ConcreteHandlerB() = default;

    void handle(int request) override
    {
        if (request == 2) {
            std::cout << "ConcreteHandlerB" << std::endl;
        } else {
            if (m_successor != nullptr) {
                m_successor->handle(request);
            } else {
                std::cout << "Cannot handle request" << std::endl;
            }
        }
    }
};

int main()
{
    auto handlerA = std::make_shared<ConcreteHandlerA>();
    auto handlerB = std::make_shared<ConcreteHandlerB>();
    handlerA->SetSuccessor(handlerB);

    handlerA->handle(0);
    handlerA->handle(1);
    handlerA->handle(2);


    return 0;
}
