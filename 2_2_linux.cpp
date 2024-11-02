#include <iostream>
#include <fstream>
#include <unistd.h>

int main() {
    std::ifstream file("Example. txt");

    if (!file.is_open()) 
    {
        std::cerr << "Unable to open the file for reading." << std::endl;
        return 1;
    }

    int handlel = file.rdbuf()->pubseekoff(10, std::ios_base::beg);
    int handle2 = dup(fileno(file.rdbuf()));
    file.close();

    std::ifstream file2("example.txt");
    int handle3 = fileno(file2.rdbuf());

    std::cout << "Handles: " << handlel << ", " << handle2 << ", " << handle3 << std::endl;
    char buffer1[8], buffer2[8], buffer3[8];

    file.rdbuf() ->pubseekpos(0) ;

    file.read(buffer1, 7);

    file2.read(buffer2, 7);

    read(handle2, buffer3, 7);

    std::cout << "Read from handlel: " << buffer1 << std::endl;

    std::cout << "Read from handle2: " << buffer2 << std::endl;
    std::cout << "Read from handle3: " << buffer3 << std::endl;

    file.close();
    file2.close();

    return 0;
}