#include <iostream>
#include <cstring>

using namespace std;

class Prototype {
public:
    Prototype() = default;
    virtual ~Prototype() = default;
    virtual Prototype *clone() = 0;
    virtual void setId(char *id) = 0;
    virtual const char *getId() const = 0;
};

class ConcretePrototype : public Prototype {
public:
    ConcretePrototype(const char *id) : m_id(strdup(id)) {};
    virtual ~ConcretePrototype()
    {
        free(m_id);
        m_id = nullptr;
    }

    void setId(char *id)
    {
        id = m_id;
    }

    virtual const char *getId() const
    {
        return m_id;
    }

    virtual Prototype *clone()
    {
        Prototype *p = new ConcretePrototype(m_id);
        p->setId(strdup(m_id));
        return p;
    }
private:
    char *m_id {nullptr};
};

int main()
{
    Prototype *p = new ConcretePrototype("HelloWorld");
    Prototype *cp = p->clone();
    std::cout << std::string(p->getId()) << std::endl;
    std::cout << std::string(cp->getId()) << std::endl;
    delete p;
    delete cp;

    return 0;
}
