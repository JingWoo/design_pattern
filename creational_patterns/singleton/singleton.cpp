#include <iostream>
#include <string>
#include <vector>
#include <atomic>
#include <mutex>

using namespace std;

class Singleton {
public:
    static std::atomic<Singleton *> m_instance;
    static Singleton *getInstance() noexcept;
    void recordResource(const std::string &msg);
    std::vector<std::string>::size_type getResourceSize() const;

private:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    static std::mutex m_mutex;
    std::vector<std::string> m_resource;
};

std::atomic<Singleton *> Singleton::m_instance;
std::mutex Singleton::m_mutex;

Singleton *Singleton::getInstance() noexcept
{
    Singleton *instance = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lock(m_mutex);
        instance = m_instance.load(std::memory_order_relaxed);
        if (instance == nullptr) {
            instance = new Singleton;
            std::atomic_thread_fence(std::memory_order_release);
            m_instance.store(instance, std::memory_order_relaxed);
        }
    }
    return instance;
}

void Singleton::recordResource(const std::string &msg)
{
    m_resource.push_back(msg);
}

std::vector<std::string>::size_type Singleton::getResourceSize() const
{
    return m_resource.size();
}

void recordMsg(const std::string &msg)
{
    Singleton *instance = Singleton::getInstance();
    instance->recordResource(msg);
}

int main()
{
    recordMsg("Design Pattern");
    recordMsg("Singleton");

    Singleton *instance = Singleton::getInstance();
    std::cout << instance->getResourceSize() << std::endl << std::flush;

    return 0;
}
