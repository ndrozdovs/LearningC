// CleanMoveSemantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class String
{
public:
    String() = default;
    String(const char* string) {
        printf("Created!\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }

    String(const String& other) {
        printf("Copied!\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    String(String&& other) noexcept {
        printf("Moved!\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        
        other.m_Size = 0;
        other.m_Data = nullptr;
    }

    String& operator=(String&& other) noexcept {
        printf("Assigned!\n");

        if (this != &other) {
            delete[] m_Data;

            m_Size = other.m_Size;
            m_Data = other.m_Data;

            other.m_Size = 0;
            other.m_Data = nullptr;
        }

        return *this;
    }

    ~String() {
        printf("Deleted!\n");
        delete[] m_Data;
    }

    void Print() {
        for (uint32_t i = 0; i < m_Size; i++) {
            printf("%c", m_Data[i]);
        }

        printf("\n");
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

class Entity
{
public:
    Entity(const String& name)
        : m_Name(name)
    {
    }
    
    Entity(String&& name)
        : m_Name(name) // change lvalue to rvalue to call the move constructor instead of copy
    {
    }

    void PrintName() {
        m_Name.Print();
    }
private:
    String m_Name;
};

int main()
{
    Entity entity("Nikita"); // User move constructor
    entity.PrintName();

    String apple("Apple"); // Normal constructor
    String moveDest = std::move(apple); // Move contructor
    String destination;

    std::cout << "Apple: ";
    apple.Print(); // "Apple"
    std::cout << "Destination: ";
    destination.Print(); // Nothing (no data)
    
    destination = std::move(apple); // Assignment operator

    std::cout << "Apple: ";
    apple.Print(); // Nothing (we moved the data)
    std::cout << "Destination: ";
    destination.Print(); // "Apple"

    std::cin.get();
}
