#include <iostream>
#include <map>
#include <memory>

using namespace std;

class ReceiverInterface {
public:
    ReceiverInterface() = default;
    ReceiverInterface(const ReceiverInterface &) = delete;
    ReceiverInterface &operator=(const ReceiverInterface &) = delete;
    virtual ~ReceiverInterface() = default;
    virtual void Execute() = 0;
};

class ReceiverA : public ReceiverInterface {
public:
    void Execute() override
    {
        std::cout << "Receiver A excute" << std::endl;
    }
};

class ReceiverB : public ReceiverInterface {
public:
    void Execute() override
    {
        std::cout << "Receiver B excute" << std::endl;
    }
};

class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    virtual void Execute() = 0;
    virtual void SetReceiver(std::shared_ptr<ReceiverInterface> receiver) = 0;
};

class ConcreteComand : public Command {
public:
    void Execute() override
    {
        m_receiver->Execute();
    }

    void SetReceiver(std::shared_ptr<ReceiverInterface> receiver) override
    {
        this->m_receiver = std::move(receiver);
    }

private:
    std::shared_ptr<ReceiverInterface> m_receiver;
};

class Invoker {
public:
    void RegisterCommand(const std::string &cmd, std::shared_ptr<Command> c)
    {
        m_commands[cmd] = std::move(c);
    }

    void Notify()
    {
        for (auto itor = m_commands.begin(); itor != m_commands.end(); ++itor) {
            itor->second->Execute();
        }
    }

    void HandleCommand(const std::string &cmd)
    {
        auto index = m_commands.find(cmd);
        if (index == m_commands.end()) {
            std::cout << "Not a registed command : " << cmd << std::endl;
            return;
        }

        index->second->Execute();
    }

private:
    std::map<std::string, std::shared_ptr<Command>> m_commands;
};

int main()
{
    auto ca = std::make_shared<ConcreteComand>();
    auto cb = std::make_shared<ConcreteComand>();
    auto ra = std::make_shared<ReceiverA>();
    auto rb = std::make_shared<ReceiverB>();
    ca->SetReceiver(ra);
    cb->SetReceiver(rb);

    Invoker invoker;
    invoker.RegisterCommand("A", ca);
    invoker.RegisterCommand("B", cb);
    invoker.Notify();

    invoker.HandleCommand("A");
    invoker.HandleCommand("C");

    return 0;
}
