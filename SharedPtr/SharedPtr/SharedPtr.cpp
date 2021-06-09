#include <iostream>
#include <string>
#include <memory>

class Entity {
public:
    Entity() {
        std::cout << "Created Entity" << std::endl;
    }

    ~Entity() {
        std::cout << "Destroyed Entity" << std::endl;
    }

    void Print() {
        std::cout << "I am Printing" << std::endl;
    }
};

int main()
{
    // When all the references are gone, when all of stack allocated objects that keep track of shared pointers get freed from memory, that's when underlying entity gets deleted
    // So destrcutor only gets called when all of references to shared pointers are out of scope
    // When we assign a shared pointer to another shared pointer, we increase the ref count (copying)
    // When we assign a shared pointer to a weak pointer, the ref count is not increased
    {
        std::shared_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            e0 = sharedEntity;
        }
        // Shared pointer is still alive here
    }

    {
        std::weak_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            e0 = sharedEntity;
            if (e0.expired())
                std::cout << "Shared pointer expired" << std::endl;
        }
        // This is where we delete the shared pointer, because weak ptr does increase the ref count and sharedEntity is out of scope
        if (e0.expired())
            std::cout << "Shared pointer expired" << std::endl;
    }

    std::cin.get();
}