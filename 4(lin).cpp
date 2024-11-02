#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#define RED "\033[1;31m"    // красный цвет
#define GREEN "\033[4;32m"  // зеленый цвет
#define RESET_COLOR "\033[0m" // сброс цвета

void printCentered(const char* text) {
    int terminalWidth = 80; 
    int textLength = strlen(text);
    int padding = (terminalWidth - textLength) / 2;
    std::cout << "\033[" << padding << "C" << text << std::endl;
}

int main() {
    const char* filename = "input.txt"; 
    char buffer[255];
    int file;
    int length;

    struct flock lock = {F_WRLCK, SEEK_SET, 0, 0};

    file = open(filename, O_RDWR, 0600);

    if (file == -1) {
        printCentered(RED "Unable to open file." RESET_COLOR);
        return 1;
    }

    if (fcntl(file, F_SETLK, &lock) == -1) {
        printCentered(RED "Failed to lock the file. Waiting for lock..." RESET_COLOR);
        lock.l_type = F_WRLCK;
        while (fcntl(file, F_SETLKW, &lock) == -1) {
            printCentered(RED "Failed to lock the file. Retrying..." RESET_COLOR);
            sleep(1);
        }
    } else {
        printCentered(GREEN "File locked successfully." RESET_COLOR);
    }

    std::ifstream infile(filename);
    if (infile) {
        std::string fileContents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
        printCentered(GREEN "Read from file:\n" RESET_COLOR);
        std::cout << fileContents;
    } else {
        printCentered(RED "Failed to read from the file." RESET_COLOR);
    }

    sleep(7);

    lock.l_type = F_UNLCK;
    if (fcntl(file, F_SETLK, &lock) == -1) {
        printCentered(RED "Failed to unlock the file." RESET_COLOR);
    } else {
        printCentered(GREEN "File unlocked successfully." RESET_COLOR);
    }

    close(file);

    return 0;
}
