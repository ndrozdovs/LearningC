#include <iostream>

class Printable {
public:
    virtual std::string GetClassName() = 0;
};

class Entity : public Printable {
public:
    virtual std::string GetName() { return "Entity"; }

    std::string GetClassName() override { return "Entity"; }
};

class Player : public Entity {
private:
    std::string m_Name;
public:
    Player(const std::string& name)
        : m_Name(name) {}

    std::string GetName() override { return m_Name; }

    std::string GetClassName() override { return m_Name; }
};

class A : public Printable {
public:
    std::string GetClassName() override { return "A"; }
};

void PrintName(Entity* entity) {
    std::cout << entity->GetName() << std::endl;
}

void PrintClassName(Printable* obj) {
    std::cout << obj->GetClassName() << std::endl;
}

int main()
{
    // In order of us to instantiate an object of type Entity or Player, those classes need to have GetClassName() override function
    // That is because they both inherit Printable, which has it as a pure virtual function
    Entity* e = new Entity;
    Player* p = new Player("Nikita");
    A* a = new A;

    PrintClassName(e);
    PrintClassName(p);
    PrintClassName(a);

    std::cin.get();
}
