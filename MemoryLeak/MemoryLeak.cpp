// MemoryLeak.cpp : This is C++ task. Find memory leaks in the program.
//

#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

class Resource
{
public:
    Resource(int id)
    {
        this->id = id;
    }

    virtual ~Resource()
    {
        tasks.clear();
    }

    void performTask(std::string task)
    {
        tasks.push_back(task);
    }

    size_t countTasks() const
    {
        return tasks.size();
    }

    std::string getTask(int index) const
    {
        return tasks.at(index);
    }

private:
    std::vector<std::string> tasks;
    int id;
};

class Runner
{
public:
    // Destructor has to be implemented to release allocated resources
    virtual ~Runner()
    {
        for (auto i : resources)
        {
            if (nullptr != i.second)
            {
                delete i.second;
                i.second = nullptr;
            }
        }
        resources.clear();
    }

    Resource* acquireResource(int id)
    {
        auto search = resources.find(id);
        if (search == resources.end())
        {
            auto resource = new Resource(id);
            std::pair<int, Resource*> keyValue(id, resource);
            resources.insert(keyValue);
            return resource;
        }
        else
        {
            return search->second;
        }
    }

    // In this method delete statement was missing, memory needs to be released
    void releaseResource(int id)
    {
        auto search = resources.find(id);
        if (search != resources.end())
        {
            delete search->second;
            search->second = nullptr;
            resources.erase(search);
        }
    }

private:
    std::unordered_map<int, Resource*> resources;
};

#ifndef RunTests
void printResource(const Resource& resource)
{
    for (size_t i = 0; i < resource.countTasks(); i++)
    {
        if (i != 0)
        {
            std::cout << ", ";
        }

        std::cout << resource.getTask(i);
    }
    std::cout << '\n';
}

int main()
{
    Runner d;

    d.acquireResource(1)->performTask("Task11");
    d.acquireResource(2)->performTask("Task21");
    printResource(*d.acquireResource(2));
    d.releaseResource(2);

    d.acquireResource(1)->performTask("Task12");
    printResource(*d.acquireResource(1));
    d.releaseResource(1);
}
#endif
