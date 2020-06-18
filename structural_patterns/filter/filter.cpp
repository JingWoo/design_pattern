#include <iostream>
#include <list>
#include <memory>

using namespace std;

class Person {
public:
    Person(const std::string &name, const std::string &gender, const std::string &workNum)
            : m_name(name)
            , m_gender(gender)
            , m_workNum(workNum)
    {
    }
    ~Person() = default;
    const std::string &GetName() const
    {
        return m_name;
    }

    const std::string &GetGender() const
    {
        return m_gender;
    }

    const std::string &GetWorkNum() const
    {
        return m_workNum;
    }

private:
    std::string m_name;
    std::string m_gender;
    std::string m_workNum;
};

class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual std::list<Person> filter(const std::list<Person> &persons) = 0;
    virtual Filter *clone() = 0;
};

class NameFilter : public Filter {
public:
    NameFilter(const std::string &filter)
            : m_filter(filter)
    {
    }
    virtual ~NameFilter() = default;
    std::list<Person> filter(const std::list<Person> &persons) override
    {
        std::list<Person> result;
        for (auto person : persons) {
            if (person.GetName() == m_filter) {
                result.push_back(person);
            }
        }
        return result;
    }

    NameFilter *clone() override
    {
        NameFilter *filter = new NameFilter("");
        *filter = *this;
        return filter;
    }

private:
    std::string m_filter;
};

class GenderFilter : public Filter {
public:
    GenderFilter(const std::string &filter)
            : m_filter(filter)
    {
    }
    virtual ~GenderFilter() = default;
    std::list<Person> filter(const std::list<Person> &persons) override
    {
        std::list<Person> result;
        for (auto person : persons) {
            if (person.GetGender() == m_filter) {
                result.push_back(person);
            }
        }
        return result;
    }

    GenderFilter *clone() override
    {
        GenderFilter *filter = new GenderFilter("");
        *filter = *this;
        return filter;
    }

private:
    std::string m_filter;
};

class WorkNumFilter : public Filter {
public:
    WorkNumFilter(const std::string &filter)
            : m_filter(filter)
    {
    }
    virtual ~WorkNumFilter() = default;
    std::list<Person> filter(const std::list<Person> &persons) override
    {
        std::list<Person> result;
        for (auto person : persons) {
            if (person.GetWorkNum() == m_filter) {
                result.push_back(person);
            }
        }
        return result;
    }

    WorkNumFilter *clone() override
    {
        WorkNumFilter *filter = new WorkNumFilter("");
        *filter = *this;
        return filter;
    }

private:
    std::string m_filter;
};

class ListFilter : public Filter {
public:
    explicit ListFilter(std::list<std::shared_ptr<Filter>> filters)
            : m_filters(filters)
    {
    }
    virtual ~ListFilter() = default;

    std::list<Person> filter(const std::list<Person> &persons) override
    {
        std::list<Person> result = persons;
        for (auto &f : m_filters) {
            result = f->filter(result);
        }

        return result;
    }

    virtual ListFilter *clone() override
    {
        return nullptr;
    }

private:
    std::list<std::shared_ptr<Filter>> m_filters;
};

int main()
{
    std::list<Person> persons;
    persons.push_back(Person("ZhangSan", "Man", "001"));
    persons.push_back(Person("LiSi", "Man", "002"));
    persons.push_back(Person("WangWu", "Man", "003"));
    persons.push_back(Person("ZhaoLiu", "Man", "004"));
    persons.push_back(Person("Qing", "Woman", "005"));
    persons.push_back(Person("YaYa", "Woman", "006"));
    persons.push_back(Person("Jam", "Man", "007"));
    persons.push_back(Person("Jam", "Woman", "008"));

    auto nameFilter = std::make_shared<NameFilter>("Jam");
    auto genderFilter = std::make_shared<GenderFilter>("Woman");
    auto workNumFilter = std::make_shared<WorkNumFilter>("008");
    std::list<std::shared_ptr<Filter>> listFilter;
    listFilter.push_back(nameFilter);
    listFilter.push_back(genderFilter);
    listFilter.push_back(workNumFilter);

    auto filters = std::make_unique<ListFilter>(listFilter);

    auto result = filters->filter(persons);

    std::cout << "***************all person********************" << std::endl;
    for (const auto &person : persons) {
        std::cout << "name: " << person.GetName() << "\t gender: " << person.GetGender()
                  << "\t workNum: " << person.GetWorkNum() << std::endl;
    }

    std::cout << std::endl << "**************filter result******************" << std::endl;
    for (const auto &person : result) {
        std::cout << "name: " << person.GetName() << "\t gender: " << person.GetGender()
                  << "\t workNum: " << person.GetWorkNum() << std::endl;
    }

    return 0;
}
