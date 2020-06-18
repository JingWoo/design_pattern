#include <iostream>
#include <list>

using namespace std;

class Colleague;

enum class ColleagueType { TYPE_A, TYPE_B };

class Mediator {
public:
    Mediator() = default;
    virtual ~Mediator() = default;
    virtual void RegisterColleague(Colleague *colleague) = 0;
    virtual void Send(const std::string &msg, Colleague *colleague) = 0;
};

class Colleague {
public:
    Colleague(Mediator *m, ColleagueType type)
            : m_mediator(m)
            , m_type(type)
    {
        m_mediator->RegisterColleague(this);
    }

    ColleagueType GetType() const
    {
        return m_type;
    }

    virtual void Send(const std::string &msg) = 0;
    virtual void Receive(const std::string &msg) = 0;

protected:
    Mediator *m_mediator;
    ColleagueType m_type;
};

class ConcreateColleagueA : public Colleague {
public:
    ConcreateColleagueA(Mediator *m)
            : Colleague(m, ColleagueType::TYPE_A)
    {
    }
    virtual ~ConcreateColleagueA() = default;
    void Send(const std::string &msg) override
    {
        m_mediator->Send(msg, this);
    }

    void Receive(const std::string &msg) override
    {
        std::cout << "ConcreateColleagueA received : " << msg << std::endl;
    }
};

class ConcreateColleagueB : public Colleague {
public:
    ConcreateColleagueB(Mediator *m)
            : Colleague(m, ColleagueType::TYPE_B)
    {
    }
    virtual ~ConcreateColleagueB() = default;

    void Send(const std::string &msg) override
    {
        m_mediator->Send(msg, this);
    }

    void Receive(const std::string &msg) override
    {
        std::cout << "ConcreateColleagueB received : " << msg << std::endl;
    }
};

class ConcreteMediator : public Mediator {
public:
    void RegisterColleague(Colleague *colleague) override
    {
        if (colleague->GetType() == ColleagueType::TYPE_A) {
            m_colleagueAs.push_back(colleague);
        } else if (colleague->GetType() == ColleagueType::TYPE_B) {
            m_colleagueBs.push_back(colleague);
        }
    }

    void Send(const std::string &msg, Colleague *colleague) override {
        if (colleague->GetType() == ColleagueType::TYPE_A) {
            for (auto itor = m_colleagueBs.begin(); itor != m_colleagueBs.end(); ++itor) {
                (*itor)->Receive(msg);
            }
        } else if (colleague->GetType() == ColleagueType::TYPE_B) {
            for (auto itor = m_colleagueAs.begin(); itor != m_colleagueAs.end(); ++itor) {
                (*itor)->Receive(msg);
            }
        }
    }

private:
    list<Colleague *> m_colleagueAs;
    list<Colleague *> m_colleagueBs;
};

int main()
{
    auto mediator = new ConcreteMediator();
    auto A1 = new ConcreateColleagueA(mediator);
    auto A2 = new ConcreateColleagueA(mediator);
    auto B1 = new ConcreateColleagueB(mediator);
    auto B2 = new ConcreateColleagueB(mediator);

    A1->Send("A1 Request");
    std::cout << std::endl;
    A2->Send("A2 Request");
    std::cout << std::endl;
    B1->Send("B1 Request");
    std::cout << std::endl;
    B2->Send("B2 Request");
    std::cout << std::endl;

    delete A1;
    delete A2;
    delete B1;
    delete B2;
    delete mediator;

    return 0;
}
