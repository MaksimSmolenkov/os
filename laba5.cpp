#include <windows.h>
#include <iostream>

int main() {
    int x;  // ось X
    int y;  // ось Y

    // хэндлы ввода и вывода
    HANDLE file_handle;
    HANDLE input_handle;
    HANDLE output_handle;

    // хэндлы для мыши
    HANDLE hW;
    HANDLE hR;

    DWORD bw = 0, length, rc, cbRead;
    INPUT_RECORD infbuf; // указатель на структуру, которая принимает данные буфера ввода
    COORD pos1, pos2, text_coord, info_coord, writePos; // указатели на структуру координат

    char filename[] = "file.txt", buf[1024], buffer[1024], temp[1024]; // буферы
    char ch, is_new_char;   // буферы для хранения символа
    short attr = BACKGROUND_GREEN; // код для заднего фона в виде зеленного

    output_handle = GetStdHandle(STD_OUTPUT_HANDLE); // получение хэндла вывода в консоль
    input_handle = GetStdHandle(STD_INPUT_HANDLE);   // получение хэндла ввода в консоль

    // проверка на валидность хэндлов
    if (input_handle == INVALID_HANDLE_VALUE || output_handle == INVALID_HANDLE_VALUE) {
        return 1;
    }

    // открытие файла для чтения
    file_handle = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    // проверка что файл открыт
    if (file_handle == INVALID_HANDLE_VALUE) {
        sprintf(temp, "File not found\n");
        WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
        return 1; // завершение программы с кодом 1
    }

    // цикл чтения и записи в консоль текста с файла
    do {
        rc = ReadFile(file_handle, buffer, 1024, &cbRead, NULL);
        WriteFile(output_handle, buffer, cbRead, &cbRead, NULL);
    } while (cbRead != 0);

    // устанавливается режим консоли
    SetConsoleMode(input_handle, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
    // устанавливается тип событий
    infbuf.EventType = MOUSE_EVENT;

    // цикл обработки событий мыши
    while (1) {
        // чтение ввода консоли
        if (ReadConsoleInput(input_handle, &infbuf, 1, &bw)) {
            // если нажата правая кнопка мыши, то программа завершается
            if (infbuf.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
                return 0;
            // устанавиваются координаты вывода информации
            info_coord.Y = 15;
            info_coord.X = 1;
            text_coord.Y = 17;
            text_coord.X = 1;

            // если нажата левая кнопка мыши
            if (infbuf.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                // получение позиции мыши
                pos1.X = infbuf.Event.MouseEvent.dwMousePosition.X;
                pos1.Y = infbuf.Event.MouseEvent.dwMousePosition.Y;
                writePos.X = infbuf.Event.MouseEvent.dwMousePosition.X;
                writePos.Y = infbuf.Event.MouseEvent.dwMousePosition.Y;

                // копирование символов из экранного буфера ячейки консоли и запись в переменные ранее созданные
                ReadConsoleOutputCharacterA(output_handle, &ch, 1, pos1, &bw);
                ReadConsoleOutputCharacterA(output_handle, &is_new_char, 1, pos1, &bw);

                // если символ полученный не пробел, то...
                if (ch != ' ') {
                    // устанавливаются аттрибуты вывода
                    FillConsoleOutputAttribute(output_handle, 0x00, 80, text_coord, &bw);
                    // очищение буфера
                    // вывод
                 WriteConsoleOutputCharacterA(output_handle, buf, strlen(buf), text_coord, &bw);
                    // указание координат
                    SetConsoleCursorPosition(output_handle, info_coord);
                    // очищение
                    sprintf(temp, "                     ");
                    WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
                    SetConsoleCursorPosition(output_handle, info_coord);
                    // вывод координат
                    sprintf(temp, "(x = %d; y = %d)", pos1.X, pos2.Y);
                    WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
                    pos2 = pos1;
                    // если буквы большие, изменяем на размер меньше, иначе по-другому
                    if (is_new_char <= 'Z' && is_new_char >= 'A') {
                        is_new_char += 32;
                        SetConsoleCursorPosition(output_handle, writePos); // устанавливаем позицию вывода
                        SetConsoleTextAttribute(output_handle, 3); // цвет
                        sprintf(temp, "%c", is_new_char);
                        WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
                    } else if (is_new_char <= 'z' && is_new_char >= 'a') {
                        is_new_char -= 32;
                        SetConsoleCursorPosition(output_handle, writePos); // устанавливаем позицию вывода
                        SetConsoleTextAttribute(output_handle, 4); // цвет
                        sprintf(temp, "%c", is_new_char);
                        WriteFile(output_handle, temp, strlen(temp), NULL, NULL);
                    }
                    SetConsoleTextAttribute(output_handle, 15);

                    // пока символ не является пробелом, и позиция по X не в точке 0
                    while ((ch != ' ') && (pos1.X > 0)) {
                        // отнимаем
                        pos1.X--;
                        // читаем буфер
                        ReadConsoleOutputCharacterA(output_handle, &ch, 1, pos1, &bw);
                    }
                    // если символ пробел, то движемся вправо
                    if (ch == ' ')
                        pos1.X++;
                    do {
                        pos2.X++;
                       ReadConsoleOutputCharacterA(output_handle, &ch, 1, pos2, &bw);
                    } while ((ch != ' ') && (pos2.X < 80)); // проход до пробела и в области экрана позиция
                    if (ch == ' ')
                        pos2.X--;
                    bw = pos2.X - pos1.X + 1;
                    ReadConsoleOutputCharacterA(output_handle, buf, bw, pos1, &bw);
                    WriteConsoleOutputCharacterA(output_handle, buf, bw, text_coord, &bw);
                    FillConsoleOutputAttribute(output_handle, attr, bw, text_coord, &bw);
                }
            }
        }
    }
    return 0;
}
