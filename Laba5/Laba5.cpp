#include "inputData.h"
#include <iostream>
#include <cmath>
#include <string>
#include <format>
#include <windows.h>
#include <cstdlib>
#include <ctime>  
#include <shellapi.h>
#include <vector>

void setGlobalColor(HANDLE hConsole, WORD winAttr, const std::string& ansiTextCode) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    DWORD cellsCount = csbi.dwSize.X * csbi.dwSize.Y;
    COORD startCoords = { 0, 0 };
    DWORD count = 0;

    std::vector<WORD> attributes(cellsCount);

    ReadConsoleOutputAttribute(hConsole, attributes.data(), cellsCount, startCoords, &count);

    WORD newBg = winAttr & (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);

    for (DWORD i = 0; i < cellsCount; ++i) {
        attributes[i] &= ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        attributes[i] |= newBg;
    }

    WriteConsoleOutputAttribute(hConsole, attributes.data(), cellsCount, startCoords, &count);

    SetConsoleTextAttribute(hConsole, winAttr);
    std::cout << ansiTextCode << std::flush;
}

void resetEntireConsoleToDefault(HANDLE hConsole) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    DWORD cellsCount = csbi.dwSize.X * csbi.dwSize.Y;
    COORD startCoords = { 0, 0 };
    DWORD count = 0;

    WORD defaultAttr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    std::vector<WORD> attributes(cellsCount, defaultAttr);


    WriteConsoleOutputAttribute(hConsole, attributes.data(), cellsCount, startCoords, &count);

    SetConsoleTextAttribute(hConsole, defaultAttr);
    std::cout << "\033[0m" << std::flush;
}

void runCaptcha(HANDLE hConsole, HWND hwnd) {
    setGlobalColor(hConsole, BACKGROUND_BLUE, "\033[44;1;33m");

    std::cout << "\nУважаемый пользователь, наша система подозревает, что вы бот. Пожалуйста пройдите капчу в вашем браузере. @Astakhov_CORP™ 2026. All Rights Reserved." << std::endl;

    std::string url = "https://zeinsority.github.io/Laba5-CAPTCHA/";
    Sleep(2000);
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);

    std::string userToken;
    while (true) {
        std::cout << "\033[44;1;33mУважаемый пользователь, введите секретный токен с страницы для подтверждения: ";
        std::cin >> userToken;

        if (userToken.rfind("ASTAKHOV-CORP-PASSED-", 0) == 0) {
            std::cout << "\033[44;1;32mУважаемый пользователь, вы ввели верный токен, продолжайте работу. @Astakhov_CORP™ 2026. All Rights Reserved.\n" << std::endl;
            std::cin.ignore(10000, '\n');
            Sleep(1500);
            break;
        }
        else {
            std::cout << "\033[44;1;31mУважаемый пользователь, вы ввели неверный токен, попробуйте еще раз. @Astakhov_CORP™ 2026. All Rights Reserved.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    setGlobalColor(hConsole, 0, "\033[0m");
    SetForegroundWindow(hwnd);
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode = 0;
    GetConsoleMode(hConsole, &consoleMode);
    SetConsoleMode(hConsole, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_NUMERIC, "C");

    HWND hwnd = GetConsoleWindow();

    bool captchaMode = true;

    if (captchaMode) {
        runCaptcha(hConsole, hwnd);
    }

    int N = getInput("N");
    int K = getInput("K");

    if (K > N)  {
        while (true) {
            setGlobalColor(hConsole, BACKGROUND_RED, "\033[41;1;37m");
            std::cout << "Уважаемый пользователь, спешим сообщить вам, что указанный вами столбец для удаления в матрице такого размера не существует.\n"
                << "Помните, что нумерация столбцов матрицы начинается j=1. Пожалуйста введите иной столбец.\n"
                << "@Astakhov_CORP™ 2026. All Rights Reserved.\n" << std::endl;

            if (captchaMode) {
                runCaptcha(hConsole, hwnd);
            }

            setGlobalColor(hConsole, BACKGROUND_RED, "\033[41;1;37m");
            K = getInput("K");
            if (K <= N) {
                setGlobalColor(hConsole, BACKGROUND_RED, "\033[41;1;37m");
                break;
            }
        }
    }

    int* matrix = new int[N * N];
    srand(static_cast<unsigned int>(time(NULL)));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; ++j) {
            matrix[i * N + j] = rand() % 99 + 1;
        }
    }

    if (captchaMode) {
        runCaptcha(hConsole, hwnd);
    }

    setGlobalColor(hConsole, BACKGROUND_GREEN, "\033[42;1;37m");
    std::cout << "\nИсходная матрица:" << std::endl;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j == (K - 1)) {
                std::cout << "\033[47;1;31m" << matrix[i * N + j] << "\t\033[42;1;37m";
            }
            else {
                std::cout << "\033[1;33m" << matrix[i * N + j] << "\t\033[42;1;37m";
            }
        }
        std::cout << std::endl;
    }

    Sleep(3000);

    int newN = N - 1;
    int* newMatrix = new int[N * newN];

    for (int i = 0; i < N; i++) {
        int newJ = 0;
        for (int j = 0; j < N; j++) {
            if (j == (K - 1)) {
                continue;
            }
            newMatrix[i * newN + newJ] = matrix[i * N + j];
            newJ++;
        }
    }

    delete[] matrix;
    matrix = newMatrix;

    if (captchaMode) {
        runCaptcha(hConsole, hwnd);
    }

    setGlobalColor(hConsole, BACKGROUND_BLUE, "\033[44;1;37m");
    std::cout << std::format("\nМатрица после удаления {} столбца:", K) << std::endl;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < newN; ++j) {
            std::cout << "\033[1;33m" << matrix[i * newN + j] << "\t\033[44;1;37m";
        }
        std::cout << std::endl;
    }

    Sleep(5000);

    resetEntireConsoleToDefault(hConsole);

    delete[] matrix;
    return 0;

}
