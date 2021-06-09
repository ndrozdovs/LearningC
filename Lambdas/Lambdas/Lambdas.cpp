#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void ForEach(std::vector<int>& vector, const std::function<void(int)>& func) {
    for (int value : vector) {
        func(value);
    }
}

int main()
{
    int a = 5;
    std::vector<int> vec = { 3, 5, 7, 2 };

    auto it = std::find_if(vec.begin(), vec.end(), [](int value) {
        return value > 3;
        });
    std::cout << "First value in the vector that is > 3: " << *it << std::endl;

    auto lambda = [a](int value) mutable {
        a++;
        std::cout << "Vector Value: " << value << ", Captured Value: " << a << std::endl;
    };

    ForEach(vec, lambda); // Pass lambda as a parameter and call it within ForEach

    std::cin.get();
}
