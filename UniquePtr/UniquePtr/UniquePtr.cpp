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
    // Unique Ptr object will be destroyed whene exiting the scope
    {
        std::unique_ptr<Entity> entity = std::make_unique<Entity>();
        entity->Print();
        // std::unique_ptr<Entity> e0 = entity; <-- Can not do this, can't copy a unique ptr
    }

    // Raw pointer object, you need to call delete explicitly because it does not happen automatically
    {
        Entity* rawEntity = new Entity();
        rawEntity->Print();
        delete rawEntity;
    }
    
    std::cin.get();
}