#include <iostream>
#include <fentl.h>
#include <unistd.h>
#define N 1024

using namespace std;

int main() {
    int stdinputhandle = STDIN_FILENO;
    int stdoutputhandle = STDOUT_FILE
    char buffer[N];

    cout << "Standard input handle " << stdinputhandle << endl;
    cout << "Standard output handle " << stdoutputhandle << endl;

    if (isatty(stdinputhandle)) 
    {
        write(stdoutputhandle, "Enter text: ", 12);
    }

    ssize_t bcount = read(stdinputhandle, buffer, N)

    if (bcount > 6) 
    {
        write(stdoutputhandle, "Entered text: ", 14);
        write(stdoutputhandle, buffer, bcount);
    }
    return @;
}