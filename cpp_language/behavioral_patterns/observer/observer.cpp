#include <iostream>
#include <list>

using namespace std;

class Observer {
public:
    Observer() = default;
    virtual ~Observer() = default;
    virtual void Update() = 0;
};

class Subject {
public:
    void Attach(Observer *observer)
    {
        m_observers.push_back(observer);
    }
    void Dettach(Observer *observer)
    {
        m_observers.remove(observer);
    }
    void Notify()
    {
        for (auto observer : m_observers) {
            observer->Update();
        }
    }
    virtual std::string GetState() const = 0;
    virtual void SetState(const std::string &state) = 0;

private:
    std::list<Observer *> m_observers;
};

class ConcreteSubject : public Subject {
public:
    std::string GetState() const override
    {
        return m_state;
    }

    void SetState(const std::string &state) override
    {
        m_state = state;
    }

private:
    std::string m_state;
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(Subject *subject, const std::string &name)
        : m_subject(subject)
        , m_name(name)
    {
    }
    virtual ~ConcreteObserver() = default;
    void Update() override
    {
        m_observerState = m_subject->GetState();
        std::cout << "Observer :" << m_name << ", its new state is : " << m_observerState << std::endl;
    }

    std::string GetState() const
    {
        return m_observerState;
    }

    void SetState(const std::string &state)
    {
        m_observerState = state;
    }

private:
    std::string m_name;
    Subject *m_subject;
    string m_observerState;
};

int main()
{
    auto *subject = new ConcreteSubject();
    subject->SetState("123");
    auto *observerA = new ConcreteObserver(subject, "A");
    auto *observerB = new ConcreteObserver(subject, "B");
    auto *observerC = new ConcreteObserver(subject, "C");

    subject->Attach(observerA);
    subject->Attach(observerB);
    subject->Attach(observerC);

    subject->Notify();

    subject->SetState("ABC");
    subject->Notify();

    delete observerA;
    delete observerB;
    delete observerC;
    delete subject;

    return 0;
}
