#include <iostream>
#include <string>

using namespace std;

class Context {
public:
    void SetInput(const std::string &input)
    {
        m_input = input;
    }

    const std::string &GetInput() const
    {
        return m_input;
    }

    void SetOutput(const std::string &output)
    {
        m_output = output;
    }

    const std::string &GetOutput() const
    {
        return m_output;
    }

private:
    std::string m_input;
    std::string m_output;
};

class AbstractExpression {
public:
    AbstractExpression() = default;
    virtual ~AbstractExpression() = default;
    virtual void Interpret(Context *context) = 0;
};

class TerminalExpression : public AbstractExpression {
public:
    void Interpret(Context *context) override
    {
        std::cout << "TerminalExpression: " << context->GetInput() << ", " << context->GetOutput() << std::endl;
    }
};

class NonTerminalExpression : public AbstractExpression {
public:
    NonTerminalExpression(AbstractExpression *e)
        : m_expression(e)
    {
    }
    void Interpret(Context *context)
    {
        std::cout << "NonTerminalExpression: " << context->GetInput() << ", " << context->GetOutput() << std::endl;
        m_expression->Interpret(context);
    }

private:
    AbstractExpression *m_expression;
};

int main()
{
    auto context = new Context;
    context->SetInput("Hello");
    context->SetOutput("World");

    auto tae = new TerminalExpression();
    auto ntae = new NonTerminalExpression(tae);

    tae->Interpret(context);
    std::cout << std::endl;
    ntae->Interpret(context);

    delete ntae;
    delete tae;
    delete context;

    return 0;
}
