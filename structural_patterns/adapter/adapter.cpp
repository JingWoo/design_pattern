#include <iostream>

using namespace std;

// Target，客户期望的接口，可以使具体或抽象的类，也可以是接口
class Target {
    public:
        Target() = default;
        virtual ~Target() = default;

        virtual void Request() = 0;
};

// 需适配的类
class Adaptee {
    public:
        void SpecificRequest() {
            std::cout << "Adaptee" << std::endl;
        }
};

// 通过内部包装一个Adaptee对象，把源接口转换为目标接口
class Adapter : public Target {
    public:
        Adapter() :m_adaptee(new Adaptee) {}
        ~Adapter() {
            delete m_adaptee;
            m_adaptee = nullptr;
        }
        void Request() {
            // 调用Request()方法会转换成调用adaptee.SpecificRequest()
            m_adaptee->SpecificRequest();
        }

    private:
        Adaptee *m_adaptee;
};

int main()
{
    Target *target = new Adapter();
    target->Request();

    delete target;
    return 0;
}
