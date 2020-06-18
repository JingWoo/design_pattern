#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Flyweight {
public:
    Flyweight() = default;
    virtual ~Flyweight() = default;
    virtual void Operation(int extrinsicstate) = 0;
};

class ConcreteFlyweight : public Flyweight {
public:
    ConcreteFlyweight() = default;
    virtual ~ConcreteFlyweight() = default;
    void Operation(int extrinsicstate) override
    {
        std::cout << "ConcreteFlyweight : " << extrinsicstate << std::endl;
    }
};

class UnsharedConcreteFlyweight : public Flyweight {
public:
    UnsharedConcreteFlyweight() = default;
    virtual ~UnsharedConcreteFlyweight() = default;
    void Operation(int extrinsicstate) override
    {
        std::cout << "UnsharedConcreteFlyweight : " << extrinsicstate << std::endl;
    }
};

// using singleton design pattern for FlyweightFactory as a global pool
class FlyweightFactory {
public:
    std::shared_ptr<Flyweight> GetFlyweight(const std::string &key)
    {
        if (m_flyweights.find(key) == m_flyweights.end()) {
            m_flyweights[key] = make_shared<ConcreteFlyweight>();
        }
        return m_flyweights[key];
    }

private:
    std::map<std::string, std::shared_ptr<Flyweight>> m_flyweights;
};

int main()
{
    int extrinsicstate = 22; // External state

    auto f = std::make_shared<FlyweightFactory>();
    auto fx = f->GetFlyweight("X");
    // X、Y、Z Inner state
    fx->Operation(--extrinsicstate); // ConcreteFlyweight: 21

    auto fy = f->GetFlyweight("Y");
    fy->Operation(--extrinsicstate); // ConcreteFlyweight: 20

    auto fz = f->GetFlyweight("Z"); // ConcreteFlyweight: 19
    fz->Operation(--extrinsicstate);

    auto uf = std::make_shared<UnsharedConcreteFlyweight>();
    uf->Operation(--extrinsicstate); // UnsharedConcreteFlyweight: 18

    return 0;
}

