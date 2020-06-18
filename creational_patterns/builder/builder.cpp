#include <iostream>

using namespace std;

class House {
public:
    House() = default;

    void setFloor(const std::string &floor)
    {
        m_floor = floor;
    }
    void setWall(const std::string &wall)
    {
        m_wall = wall;
    }
    void setRoof(const std::string &roof)
    {
        m_roof = roof;
    }

    void show()
    {
        std::cout << m_floor << "\t" << m_wall << "\t" << m_roof << std::endl;
    }

private:
    std::string m_floor, m_wall, m_roof;
};

class AbstractBuilder {
public:
    AbstractBuilder()
            : m_house(new House)
    {
    }
    virtual ~AbstractBuilder()
    {
        delete m_house;
    }

    virtual void buildFloor() = 0;
    virtual void buildWall() = 0;
    virtual void buildRoof() = 0;
    virtual House *getHouse()
    {
        return m_house;
    }

protected:
    House *m_house { nullptr };
};

class ConcreteBuilderA : public AbstractBuilder {
public:
    ConcreteBuilderA()
            : AbstractBuilder()
    {
    }
    ~ConcreteBuilderA() = default;

    void buildFloor() override
    {
        m_house->setFloor("Floor style A");
    }

    void buildWall() override
    {
        m_house->setWall("Wall style A");
    }

    void buildRoof() override
    {
        m_house->setRoof("Roof style A");
    }
};

class ConcreteBuilderB : public AbstractBuilder {
public:
    ConcreteBuilderB()
            : AbstractBuilder()
    {
    }
    ~ConcreteBuilderB() = default;

    void buildFloor() override
    {
        m_house->setFloor("Floor style B");
    }

    void buildWall() override
    {
        m_house->setWall("Wall style B");
    }

    void buildRoof() override
    {
        m_house->setRoof("Roof style B");
    }
};

class Director {
public:
    Director() = default;
    virtual ~Director() = default;
    void setBuilder(AbstractBuilder *builder)
    {
        m_builder = builder;
    }

    House *Construct()
    {
        m_builder->buildFloor();
        m_builder->buildWall();
        m_builder->buildRoof();
        return m_builder->getHouse();
    }

private:
    AbstractBuilder *m_builder { nullptr };
};

int main()
{
    AbstractBuilder *builder = new ConcreteBuilderA();
    Director *director = new Director();
    director->setBuilder(builder);
    House *house = director->Construct();
    house->show();
    delete builder;

    builder = new ConcreteBuilderB();
    director->setBuilder(builder);
    house = director->Construct();
    house->show();
    delete builder;

    delete director;

    return 0;
}
