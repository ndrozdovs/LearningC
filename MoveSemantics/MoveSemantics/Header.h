#pragma once
class Holder
{
public:

    Holder(int size)         // Constructor
    {
        m_data = new int[size];
        m_size = size;
    }

    ~Holder()                // Destructor
    {
        delete[] m_data;
    }

    // Copy Constructor
    Holder(const Holder& other)
    {
        m_data = new int[other.m_size];  // (1)
        std::copy(other.m_data, other.m_data + other.m_size, m_data);  // (2)
        m_size = other.m_size;
    }

    // Move Constructor
    Holder(Holder&& other)     // <-- rvalue reference in input
    {
        m_data = other.m_data;   // (1)
        m_size = other.m_size;
        other.m_data = nullptr;  // (2)
        other.m_size = 0;
    }

    // Assignment Operator
    Holder& operator=(const Holder& other)
    {
        if (this == &other) return *this;  // (1)
        delete[] m_data;  // (2)
        m_data = new int[other.m_size];
        std::copy(other.m_data, other.m_data + other.m_size, m_data);
        m_size = other.m_size;
        return *this;  // (3)
    }

    // move assignment operator
    Holder& operator=(Holder&& other)     // <-- rvalue reference in input  
    {
        if (this == &other) return *this;

        delete[] m_data;         // (1)

        m_data = other.m_data;   // (2)
        m_size = other.m_size;

        other.m_data = nullptr;  // (3)
        other.m_size = 0;

        return *this;
    }

private:

    int* m_data;
    size_t m_size;
};