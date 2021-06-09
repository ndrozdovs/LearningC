#include <iostream>
#include <fstream>
#include <optional>
#include <string>

std::optional<std::string> ReadFileAsString(const std::string& filepath) {
    std::ifstream stream(filepath);
    if (stream) {
        std::string result;
        std::getline(stream, result);
        stream.close();
        return result;
    }

    return {};
}

int main()
{
    std::optional<std::string> data = ReadFileAsString("data.txt");

    std::string value = data.value_or("Not present");
    std::cout << value << std::endl;

    if (data.has_value()) {
        std::cout << "File read succesfully!" << std::endl;
    }
    else {
        std::cout << "File could not be opened!" << std::endl;
    }

    std::cin.get();
}