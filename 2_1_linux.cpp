#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("Example.txt")

    if (!file.is_open()) 
    {
        std::cerr << "Unable to open the file for writing." << std::endl;
        return 1;

    }

    std::cout << "Enter text: \n";

    std::string input;

    while (std::getline(std::cin, input))
    {
        file << input << std::endl;
    }

    file.close();
    std::cout << "File created successfully." << std::endl;

    return 0;

}
