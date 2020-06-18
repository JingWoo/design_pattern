#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Iterator {
public:
    Iterator() = default;
    virtual ~Iterator() = default;
    virtual std::string First() = 0;
    virtual std::string Next() = 0;
    virtual std::string CurrentItem() = 0;
    virtual bool IsDone() = 0;
};

class Aggregate {
public:
    virtual Iterator *CreateIterator() = 0;
    virtual void Push(std::string s) = 0;
    virtual std::string Pop(int index) = 0;
    virtual int Count() = 0;
};

class ConcreteIterator : public Iterator {
public:
    ConcreteIterator(Aggregate *a)
        : m_aggregate(a)
    {
    }

    std::string First() override
    {
        return m_aggregate->Pop(0);
    }

    std::string Next() override
    {
        std::string res;
        index++;
        if (index < m_aggregate->Count()) {
            res = m_aggregate->Pop(index);
        }
        return res;
    }

    bool IsDone() override
    {
        return index >= m_aggregate->Count();
    }

    std::string CurrentItem() override
    {
        return m_aggregate->Pop(index);
    }

private:
    Aggregate *m_aggregate;
    int index {};
};

class ConcreteAggregate : public Aggregate {
public:
    ConcreteAggregate()
    {
        m_items.clear();
        m_itor = nullptr;
    }
    virtual ~ConcreteAggregate()
    {
        if (m_itor != nullptr) {
            delete m_itor;
            m_itor = nullptr;
        }
    }

    Iterator *CreateIterator() override
    {
        if (m_itor == nullptr) {
            m_itor = new ConcreteIterator(this);
        }
        return m_itor;
    }

    void Push(std::string s) override
    {
        m_items.push_back(s);
    }

    std::string Pop(int index) override
    {
        std::string res;
        if (index < Count()) {
            res = m_items.at(index);
        }

        return res;
    }

    int Count() override
    {
        return m_items.size();
    }

private:
    std::vector<std::string> m_items;
    Iterator *m_itor;
};

int main()
{
    auto ca = new ConcreteAggregate();
    ca->Push("A");
    ca->Push("B");

    auto itor = ca->CreateIterator();
    while (!itor->IsDone()) {
        std::cout << itor->CurrentItem() << std::endl;
        itor->Next();
    }

    delete ca;

    return 0;
}
