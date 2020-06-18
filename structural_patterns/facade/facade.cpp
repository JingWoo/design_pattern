#include <iostream>

using namespace std;

class SubSystemOne {
public:
    void MethodOne()
    {
        std::cout << "SubSystemOne" << std::endl;
    }
};

class SubSystemTwo {
public:
    void MethodTwo()
    {
        std::cout << "SubSystemTwo" << std::endl;
    }
};

class SubSystemThree {
public:
    void MethodThree()
    {
        std::cout << "SubSystemThree" << std::endl;
    }
};

class Facade {
public:
    void MethodA()
    {
        s1.MethodOne();
        s2.MethodTwo();
    }

    void MethodB()
    {
        s2.MethodTwo();
        s3.MethodThree();
    }

private:
    SubSystemOne s1;
    SubSystemTwo s2;
    SubSystemThree s3;
};

int main()
{
    Facade facade;
    facade.MethodA();
    facade.MethodB();

    return 0;
}
