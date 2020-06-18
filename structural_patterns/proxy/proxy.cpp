#include <iostream>
#include <memory>

using namespace std;

class Subject {
public:
    virtual void Request() = 0;
    virtual ~Subject() = default;
};

class RealSubject : public Subject {
public:
    void Request() override
    {
        std::cout << "RealSubject" << std::endl;
    }
};

class Proxy : public Subject {
public:
    void Request() override
    {
        std::cout << "Proxy::before" << std::endl;
        if (m_realSubject == nullptr) {
            m_realSubject = new RealSubject();
        }
        m_realSubject->Request();
        std::cout << "Proxy::after" << std::endl;
    }
    virtual ~Proxy()
    {
        delete m_realSubject;
        m_realSubject = nullptr;
    }

private:
    RealSubject *m_realSubject;
};

int main()
{
    auto proxy = std::make_unique<Proxy>();
    proxy->Request();

    return 0;
}
