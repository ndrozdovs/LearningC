#include <iostream>
#include <vector>

void HelloWorld(int a ) {
    std::cout << "Hello World Value: " << a << std::endl;
}

void ForEach(std::vector<int>& vector, void(*func)(int)) {
    for (int value : vector) {
        func(value);
    }
}

void PrintValue(int value) {
    std::cout << "Value: " << value << std::endl;
}

int main()
{
    typedef void(*HelloWorldFunction)(int); // Function pointer typedef
    std::vector<int> vec = { 3, 5, 7, 2 };

    HelloWorldFunction function = HelloWorld; // function point to HelloWorld function
    function(8); // Call Hello World

    ForEach(vec, PrintValue); // Pass function as a parameter and call it within ForEach

    // Using a lambda, an anonymous function
    ForEach(vec, [](int value) { 
        std::cout << "(Inline) Value: " << value << std::endl; 
    });

    std::cin.get();
}
