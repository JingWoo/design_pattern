#include <iostream>
#include <string>
#include <memory>

using namespace std;

class animal {
public:
    virtual void make_sound() const = 0;
};

class dog : public animal {
    virtual void make_sound() const override
    {
        std::cout << "woof!" << std::endl;
    }
};

class null_animal : public animal {
    virtual void make_sound() const override
    {
    }
};

// function which requires an animal instance,
// and will not accept null
void do_something(const animal &Inst)
{
    // Inst may never be null here
}

// function which may accept an animal instance or null
void do_something(const animal *pInst)
{
    // pInst may be null
}
