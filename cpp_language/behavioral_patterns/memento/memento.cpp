#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Memento {
public:
    Memento() = default;
    virtual ~Memento() = default;
    virtual std::string Name() const = 0;
    virtual std::string Date() const = 0;
    virtual std::string State() const = 0;
};

class ConcreteMemento : public Memento {
public:
    ConcreteMemento(const std::string &state)
        : m_state(state)
    {
        std::time_t now = std::time(0);
        this->m_date = std::ctime(&now);
    }

    std::string Name() const override
    {
        return this->m_date + " / (" + this->m_state.substr(0, 9) + "...)";
    }

    std::string Date() const override
    {
        return m_date;
    }

    std::string State() const override
    {
        return m_state;
    }

private:
    std::string m_date;
    std::string m_state;
};

class Originator {
public:
    Originator(const std::string &state)
        : m_state(state)
    {
        std::cout << "Originator: Initial state is " << m_state << std::endl;
    }

    void DoSomething()
    {
        std::cout << "Originator: I'm doing something important." << std::endl;
        m_state = GenerateRandomString(30);
        std::cout << "Originator: and my state has changed to: " << m_state << std::endl;
    }

    Memento *Save()
    {
        return new ConcreteMemento(m_state);
    }

    void Restore(Memento *memento)
    {
        m_state = memento->State();
        cout << "Originator: My state has changed to: " << m_state << std::endl;
    }

private:
    std::string GenerateRandomString(int length = 10)
    {
        const char alphanum[] = "0123456789"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        std::string random_string;
        for (int i = 0; i < length; i++) {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

private:
    std::string m_state;
};

class Caretaker {
public:
    Caretaker(Originator *originator)
        : m_originator(originator)
    {
    }
    void Backup()
    {
        std::cout << std::endl << "Caretaker: Saving Originator's state..." << std::endl;
        m_mementos.push_back(m_originator->Save());
    }

    void Undo()
    {
        if (!m_mementos.size()) {
            return;
        }
        auto memento = m_mementos.back();
        m_mementos.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->Name() << std::endl;
        try {
            m_originator->Restore(memento);
        } catch (...) {
            Undo();
        }
    }

    void ShowHistory() const
    {
        std::cout << "Caretaker: Here's the list of mementos:" << std::endl;
        for (auto memento : m_mementos) {
            std::cout << memento->Name() << std::endl;
        }
    }

private:
    Originator *m_originator;
    std::vector<Memento *> m_mementos;
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    std::cout << "\n";
    caretaker->ShowHistory();
    std::cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->Undo();
    std::cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;

    return 0;
}

