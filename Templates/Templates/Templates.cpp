// Templates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template<typename T>
void Print(T value) {
    std::cout << value << std::endl;
}

template<typename T, int N>
class Array {
private:
    T m_Array[N];
public:
    int GetSize() const { return N; }
};

int main()
{
    Print<std::string>("Hello");
    
    Array<int, 5> arrayObj;
    std::cout << arrayObj.GetSize() << std::endl;
}