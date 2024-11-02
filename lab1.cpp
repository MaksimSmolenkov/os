#include <iostream>
#include <Windows.h>
#define N 1024

using namespace std;

int main() {
    HANDLE stdinputhandle = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdoutputhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    char buffer[N];
    DWORD bcount;
    cout << "Standard input handle " << stdinputhandle << endl;
    cout << "Standard output handle " << stdoutputhandle << endl;
    if (GetFileType(stdinputhandle) == FILE_TYPE_CHAR) WriteFile(stdoutputhandle, "Enter text: ", 12, NULL, NULL);
    ReadFile(stdinputhandle, buffer, N, &bcount, NULL);
    WriteFile(stdoutputhandle, "Entered text: ", 14, NULL, NULL);
    WriteFile(stdoutputhandle, buffer, bcount, NULL, NULL);
    return 0;
}