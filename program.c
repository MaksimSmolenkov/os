#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 255
#define SLEEP_DURATION_BEFORE_RETRY 100
#define SLEEP_DURATION_AFTER_SUCCESS 7000

HANDLE output, file_handle;

void gotoxy(int x, int y) {
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(output, coordinates);
}

void printCentered(char* text, int y, WORD color) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(output, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int x = (consoleWidth - strlen(text)) / 2;

    gotoxy(x, y);
    SetConsoleTextAttribute(output, color);
    WriteFile(output, text, strlen(text), NULL, NULL);
}

int main() {
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD length;
    int error = 0;
    char temp[BUFFER_SIZE];
    RECT rect = { 0 };
    GetWindowRect(GetConsoleWindow(), &rect);
    int y = (rect.bottom - rect.top) / 2;

    do {
        system("cls");
        file_handle = CreateFile("file.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        printCentered("file handle:", y, 10);
        sprintf(temp, "%d", file_handle);
        printCentered(temp, y + 1, 10);

        if (file_handle == INVALID_HANDLE_VALUE) {
            error = GetLastError();

            printCentered("error:", y + 2, 4);
            sprintf(temp, "%d", error);
            printCentered(temp, y + 3, 4);

            if (error == ERROR_FILE_NOT_FOUND) {
                printCentered("File not found", y + 4, 4);
                Sleep(SLEEP_DURATION_AFTER_SUCCESS);
                return 0;
            }

            if (error == ERROR_SHARING_VIOLATION) {
                printCentered("File is in use", y + 4, 4);
            }
        } else {
            break;
        }

        Sleep(SLEEP_DURATION_BEFORE_RETRY);
    } while (1);

    printCentered("File open!", y + 4, 14);

    ReadFile(file_handle, temp, BUFFER_SIZE - 1, &length, NULL);
    temp[length] = '\0'; // Null-terminate the string

    printCentered(temp, y + 6, 15);

    Sleep(SLEEP_DURATION_AFTER_SUCCESS);
    CloseHandle(file_handle);
    return 0;
}
