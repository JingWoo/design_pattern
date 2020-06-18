#include <iostream>
#include <list>
#include <string>

using namespace std;

// 为组合中的对象声明接口，在适当情况下，实现所有类共有接口的默认行为
class Component {
public:
    Component(const std::string &name)
            : m_name(name)
    {
    }
    virtual ~Component() = default;
    virtual void Add(Component *c) = 0;
    virtual void Remove(Component *c) = 0;
    virtual void Display(int depth) = 0;

protected:
    std::string m_name;
};

// 在组合中表示叶节点对象，叶节点没有子节点
class Leaf : public Component {
public:
    Leaf(const std::string &name)
            : Component(name)
    {
    }
    void Add(Component *c) override
    {
    }
    void Remove(Component *c) override
    {
    }
    void Display(int depth) override
    {
        std::cout << m_name << "\t" << depth << std::endl;
    }
};

// 定义有枝节点行为，用来存储子部件
class Composite : public Component {
public:
    Composite(const std::string &name)
            : Component(name)
    {
    }
    virtual ~Composite()
    {
    }
    void Add(Component *c) override
    {
        m_list.push_back(c);
    }

    void Remove(Component *c) override
    {
        m_list.remove(c);
    }

    void Display(int depth) override
    {
        std::cout << m_name << "\t" << depth << std::endl;
        for (auto itor = m_list.begin(); itor != m_list.end(); ++itor) {
            (*itor)->Display(depth + 1);
        }
    }

private:
    list<Component *> m_list;
};

int main()
{
    Composite *root = new Composite("root");
    root->Add(new Leaf("Leaf A"));
    root->Add(new Leaf("Leaf B"));

    Composite *comp = new Composite("Composite X");
    comp->Add(new Leaf("Leaf XA"));
    comp->Add(new Leaf("Leaf XB"));
    root->Add(comp);

    Composite *comp2 = new Composite("Composite XY");
    comp2->Add(new Leaf("Leaf XYA"));
    comp2->Add(new Leaf("Leaf XYB"));
    comp->Add(comp2);

    root->Display(1);

    return 0;
}
