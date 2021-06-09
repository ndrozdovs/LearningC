// TrailingReturnTypes+Decltype.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>

// NOTE: This does not compile!
#if 0
template <typename T, typename U>
decltype(a + b) add(T a, U b) {
    return a + b;
}
#endif

// Trailing return types allows this:
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main()
{
    // decltype examples
    // decltype is an operator which returns the declared type of an expression passed to it. cv-qualifiers and references are maintained if they are part of the expression
    int a = 1; // `a` is declared as type `int`
    decltype(a) b = a; // `decltype(a)` is `int`
    const int& c = a; // `c` is declared as type `const int&`
    decltype(c) d = a; // `decltype(c)` is `const int&`
    decltype(123) e = 123; // `decltype(123)` is `int`
    int&& f = 1; // `f` is declared as type `int&&`
    decltype(f) g = 1; // `decltype(f) is `int&&`
    decltype((a)) h = g; // `decltype((a))` is int&

    // Trailing return types
    // C++11 allows functions and lambdas an alternative syntax for specifying their return types

    // Lambda example of specifiying a return type
#if 0
    auto g = []() -> int {
        return 123;
    };
#endif

    std::cout << "Adding 2 + 3: " << add(2, 3) << std::endl; // int
    std::cout << "Adding 2.2 + 3: " << add(2.2, 3) << std::endl; // double
}
