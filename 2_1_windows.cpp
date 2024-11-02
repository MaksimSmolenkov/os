#include <iostream>
#include <fstream>
#include <Windows.h>
#define N 1024

int main() {
    char buffer[N];
    DWORD length;
    HANDLE input, output;
    const wchar_t file[] = L"file.txt";
    BOOL readSuccess;

    input = GetStdHandle(STD_INPUT_HANDLE);
    if (input = INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    output = CreateFile(file, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    if (output == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error in file opening" << std::endl;
        return 0;
    }

    std::cout << "Enter text: " << std::endl;
    readSucces = ReadFile(input, buffer, 80, &length, NULL);
    if (!readSucces)
    {
        std::cout << "Error in reading file" << std::endl;
        return 0;
    }

    WriteLine(output, buffer, length, &length, NULL);
    std::cout << "File created successfully" << std::endl;
    CloseHandle(output);
    
    return 0;
}

    