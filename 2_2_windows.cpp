#include <iostream>
#include <Windows.h>

int main()
{
    char buffer[255];
    DWORD length;
    HANDLE input,
        file_one,
        file_two,
        file_three,
        output_console;
    wchar_t name[] = L"file.txt";
    BOOL readSuccess;

    input = GetStdHandle(STD_INPUT_HANDLE);
    output_console = GetStdHandle(STD_OUTPUT_HANDLE);
    file_one = CreateFIle(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    DuplicateHandle(GetCurrentProccess(),
        file_one, GetCurrentProccess(), &file_two,
        0, FALSE, DUPLICATE_SAME_ACCESS);

    file_three = CreateFIle(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (file__three == INVALID_HANDLE_VALUE) return 0;

    std::cout << file_one << ", " << file_two << ", " << file_three << std::endl;

    SetFilePointer(file_one, 10, 0, FILE_BEGIN);

    readSuccess = ReadFile(file_one, buffer, 80, &length, NULL);
    WriteFile(output_console, buffer, 7, &length, NULL);

    readSuccess = ReadFile(file_two, buffer, 80, &length, NULL);
    WriteFile(output_console, buffer, 7, &length, NULL);

    readSuccess = ReadFile(file_three, buffer, 80, &length, NULL);
    WriteFile(output_console, buffer, 7, &length, NULL);

    CloseHandle(file_one);
    CloseHandle(file_two);
    CloseHandle(file_three);

    std::cin.get();
    return 0;
}
