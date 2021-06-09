#include <iostream>

class Entity {
public:
    float X, Y;

    void Move(float xa, float ya) {
        X += xa;
        Y += ya;
    }

    virtual std::string GetName() {
        return "Entity";
    }
};

class Player : public Entity {
private: 
    std::string m_Name;
public:
    Player(const std::string& name)
        : m_Name(name) {}

    std::string GetName() override {
        return m_Name;
    }
};

void PrintName(Entity* entity) {
    std::cout << entity->GetName() << std::endl;
}

int main()
{
    std::cout << sizeof(Player) << std::endl; // Size is of variables of Player and Entity, since Player inherits from Entity

    // When creating object on the stack, it is automatically destroyed when exiting the scope
    {
        Player stackPlayer("Nikita"); // Creates a Player object on the stack and is destroyed when out of scope
        stackPlayer.Move(5, 5);
        stackPlayer.X = 2;
    }
    // stackPlayer.GetName(); // stackPlayer is undefined because we exited the scope

    // When creating an object on the heap, we need to call delete to destroy it
    Player* heapPlayer;
    {
        heapPlayer = new Player("Nikita");
        heapPlayer->Move(2, 2);
    }
    heapPlayer->X = 3;
    delete heapPlayer;

    // VIRTUAL
    Entity* e = new Entity();
    std::cout << "Entity Direct Call: " << e->GetName() << std::endl; // Prints Entity
    PrintName(e); // Print Entity

    Player* p = new Player("Nikita");
    std::cout << "Player Direct Call: " << p->GetName() << std::endl; // Prints Nikita
    PrintName(p); // Prints Entity unless we add a virtual keyword to Entity GetName() and override to Player GetName()

    std::cin.get();
}
