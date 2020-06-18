#include <iostream>
#include <list>

using namespace std;

// eg:
// ObjectStructure=>city(hangzhou)
// ConcreteElementN=>place(xihu)
// ConcreteElementN=>place(zhejiang univerity)
// ConcreteVisitorA => person(student)
// ConcreteVisitorB => person(teacher)
// ConcreteVisitorC => person(tourist) 

class ConcreteElementN;
class ConcreteElementM;

class Visitor {
public:
    Visitor() = default;
    virtual ~Visitor() = default;
    virtual void Visit(ConcreteElementN *) = 0;
    virtual void Visit(ConcreteElementM *) = 0;
};

class ConcreteVisitorA : public Visitor {
public:
    void Visit(ConcreteElementN *elem) override
    {
        std::cout << "ConcreteVisitorA visit elemN" << std::endl;
    }

    void Visit(ConcreteElementM *elem) override
    {
        std::cout << "ConcreteVisitorA visit elemM" << std::endl;
    }
};

class ConcreteVisitorB : public Visitor {
public:
    void Visit(ConcreteElementN *elem) override
    {
        std::cout << "ConcreteVisitorB visit elemN" << std::endl;
    }

    void Visit(ConcreteElementM *elem) override
    {
        std::cout << "ConcreteVisitorB visit elemM" << std::endl;
    }
};

class ConcreteVisitorC : public Visitor {
public:
    void Visit(ConcreteElementN *elem) override
    {
        std::cout << "ConcreteVisitorC visit elemN" << std::endl;
    }

    void Visit(ConcreteElementM *elem) override
    {
        std::cout << "ConcreteVisitorC visit elemM" << std::endl;
    }
};

class Element {
public:
    Element() = default;
    virtual ~Element() = default;
    virtual void Accept(Visitor *visitor) = 0;
};

class ConcreteElementN : public Element {
public:
    void Accept(Visitor *visitor)
    {
        std::cout << "ConcreteElementN: ";
        visitor->Visit(this);
    }
};

class ConcreteElementM : public Element {
public:
    void Accept(Visitor *visitor)
    {
        std::cout << "ConcreteElementM: ";
        visitor->Visit(this);
    }
};

class ObjectStructure {
public:
    void Attach(Element *elem) {
        m_elements.push_back(elem);
    }
    void Detach(Element *elem) {
        m_elements.remove(elem);
    }

    void Accept(Visitor *visitor) {
        for (auto itor = m_elements.begin(); itor != m_elements.end(); ++itor) {
            (*itor)->Accept(visitor);
        }
    }

private:
    std::list<Element *> m_elements;
};

int main()
{
    auto os = new ObjectStructure();
    auto elemN = new ConcreteElementN();
    auto elemM = new ConcreteElementM();

    auto visitorA = new ConcreteVisitorA();
    auto visitorB = new ConcreteVisitorB();
    auto visitorC = new ConcreteVisitorC();

    os->Attach(elemN);
    os->Attach(elemM);

    os->Accept(visitorA);
    os->Accept(visitorB);
    os->Accept(visitorC);

    delete visitorA;
    delete visitorB;
    delete visitorC;
    delete elemN;
    delete elemM;
    delete os;

    return 0;

}
