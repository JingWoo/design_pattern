#include <iostream>

using namespace std;

class Strategy {
public:
    Strategy() = default;
    virtual ~Strategy() = default;

    virtual void AlgorithmInterface() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void AlgorithmInterface() override
    {
        std::cout << "Algorithm A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void AlgorithmInterface() override
    {
        std::cout << "Algorithm B" << std::endl;
    }
};

class ConcreteStrategyC : public Strategy {
public:
    void AlgorithmInterface() override
    {
        std::cout << "Algorithm C" << std::endl;
    }
};

class Context {
public:
    void SetAlgorithm(Strategy *s)
    {
        m_strategy = s;
    }
    void ExecuteAlgorithm()
    {
        if (m_strategy == nullptr) {
            std::cerr << "Not configure algorithm strategy" << std::endl;
        }
        m_strategy->AlgorithmInterface();
    }

private:
    Strategy *m_strategy;
};

int main()
{
    auto strategyA = new ConcreteStrategyA();
    auto strategyB = new ConcreteStrategyB();
    auto strategyC = new ConcreteStrategyC();
    auto context = new Context();
    context->SetAlgorithm(strategyA);
    context->ExecuteAlgorithm();

    context->SetAlgorithm(strategyB);
    context->ExecuteAlgorithm();

    context->SetAlgorithm(strategyC);
    context->ExecuteAlgorithm();

    delete context;
    delete strategyA;
    delete strategyB;
    delete strategyC;

    return 0;
}
