// Namespaces.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// Simple way to create classes in a name space
namespace simple {
    class Dog {
    public:
        void Print() {
            std::cout << "simple::Dog::Print()" << std::endl;
        }
    };
}

// Class can also be declared inside namespace and defined outside namespace
namespace outside {
    class Cat;
}

class outside::Cat {
public:
    void Print() {
        std::cout << "outside::Cat::Print()" << std::endl;
    }
};

// We can define methods also outside the namespace
namespace outsideMethod {
    void Print();
    class Animal {
    public:
        void Print();
    };
}

void outsideMethod::Print() {
    std::cout << "outsideMethod::Print()" << std::endl;
}

void outsideMethod::Animal::Print() {
    std::cout << "outsideMethod::animal::Print()" << std::endl;
}

// Nested namespace
namespace first {
    int value1 = 5;
    namespace second {
        int value2 = value1;
    }
}

// Namespace aliasing
namespace name1 {
    namespace name2 {
        namespace name3{
            int var = 47;
        }
    }
}

// Inline namespace
namespace ns1 {
    inline namespace ns2 {
        inline namespace ns3 {
            int var = 10;
        }
    }
}

int main()
{
    simple::Dog doggy;
    outside::Cat kitty;
    outsideMethod::Animal animal;

    doggy.Print(); // Prints simple::Dog::Print()
    kitty.Print(); // Prints outside::Cat::Print()
    animal.Print(); // Prints outsideMethod::animal::Print()
    outsideMethod::Print(); // Prints outsideMethod::Print()

    std::cout << "Nested namespace: " << first::second::value2 << std::endl; // Prints 5

    // Alias
    namespace alias = name1::name2::name3;
    std::cout << "Namespace with an alias: " << alias::var << std::endl; // Prints 47

    // Inline namespace
    // The inline specifier makes the declarations from the nested namespace appear exactly as if they had been declared in the enclosing namespace
    // This means it drags out the declaration (“var” in the below example) from a nested namespace to the containing namespace
    std::cout << "Inline namespace: " << ns1::var << std::endl;

    std::cin.get();
}