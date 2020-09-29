#include <iostream>

using namespace std;

class Context;

class State {
public:
    State() = default;
    virtual ~State() = default;
    virtual void Handle(Context *c) = 0;
};

class Context {
public:
    void SetState(State *s)
    {
        m_state = s;
    }

    void Request()
    {
        m_state->Handle(this);
    }

private:
    State *m_state;
};

class ConcreateStateA : public State {
public:
    void Handle(Context *c) override;
};

class ConcreateStateB : public State {
public:
    void Handle(Context *c) override;
};

class ConcreateStateC : public State {
public:
    void Handle(Context *c) override;
};

void ConcreateStateA::Handle(Context *c)
{
    std::cout << "ConcreateStateA" << std::endl;
    c->SetState(new ConcreateStateB);
}

void ConcreateStateB::Handle(Context *c)
{
    std::cout << "ConcreateStateB" << std::endl;
    c->SetState(new ConcreateStateC);
}

void ConcreateStateC::Handle(Context *c)
{
    std::cout << "ConcreateStateC" << std::endl;
    c->SetState(new ConcreateStateA);
}

int main()
{
    auto state = new ConcreateStateA();
    auto context = new Context();
    context->SetState(state);
    context->Request();
    context->Request();
    context->Request();

    delete context;
    delete state;

    return 0;
}
