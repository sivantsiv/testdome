// VeterinarianDatabase.cpp : This is C++ task. Implement accept() and heal() methods of Veterinarian database.
//

#include <string>
#include <iostream>
#include <stdexcept>
#include <queue>

class Veterinarian
{
public:
    void accept(std::string petName)
    {
        if (0 != petName.size())
        {
            database.push(petName);
        }
    }

    std::string heal()
    {
        if (0 == database.size())
        {
            throw std::logic_error("Clinic is empty!");
        }

        std::string petName = database.front();
        database.pop();
        return petName;
    }

private:

    std::queue<std::string> database;
};

#ifndef RunTests
int main()
{
    Veterinarian veterinarian;
    veterinarian.accept("Barkley");
    veterinarian.accept("Mittens");
    std::cout << veterinarian.heal() << std::endl;
    std::cout << veterinarian.heal() << std::endl;
}
#endif
