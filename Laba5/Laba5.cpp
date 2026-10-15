#include "inputData.h"
#include <iostream>
#include <cmath>
#include <string>
#include <format>
#include <windows.h>
#include <cstdlib>
#include <ctime>  
#include <shellapi.h>

void runCaptcha(HANDLE hConsole) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD currentColors = csbi.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << "\nУважаемый пользователь, наша система подозревает, что вы бот. Пожалуйста пройдите капчу в вашем браузере. @Team_Autism™ 2026. All Rights Reserved." << std::endl;

    std::string url = "https://zeinsority.github.io/Laba5-CAPTCHA/";

    Sleep(2000);

    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);

    std::string userToken;
    while (true) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "Уважаемый пользователь, введите секретный токен с страницы для подтверждения: ";
        std::cin >> userToken;

        if (userToken.rfind("TEAM-AUTISM-PASSED-", 0) == 0) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            std::cout << "Уважаемый пользователь, вы ввели верный токен, продолжайте работу. @Team_Autism™ 2026. All Rights Reserved.\n" << std::endl;

            std::cin.ignore(10000, '\n');

            break;
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::cout << "Уважаемый пользователь, вы ввели неверный токен, попробуйте еще раз. @Team_Autism™ 2026. All Rights Reserved." << std::endl;
        }
    }

    SetConsoleTextAttribute(hConsole, currentColors);
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_NUMERIC, "C");

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD oldColorAttrs = csbi.wAttributes;

    COORD bufferSize;
    bufferSize.X = 2000;
    bufferSize.Y = 4000;
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    bool captchaMode = true;

    if (captchaMode) { 
        runCaptcha(hConsole); 
    }

	int N = getInput("N");

    if (captchaMode) { 
        runCaptcha(hConsole); 
    }

	int K = getInput("K");

    if (K > N) {
        while (true) {
            std::cout << "Уважаемый пользователь, спешим сообщить вам, что указанный вами столбец для удаления в матрице такого размера не существует. Помните, что нумерация столбцов матрицы начинается j=1. Пожалуйста введите иной столбец. @Team_Autism™ 2026. All Rights Reserved." << std::endl;
            
            if (captchaMode) { runCaptcha(hConsole); }
            K = getInput("K");
            if (K <= N) { 
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

    if (captchaMode) { runCaptcha(hConsole); }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << "\nИсходная матрица:" << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j == (K - 1)) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            std::cout << matrix[i * N + j] << "\t";
        }
        std::cout << std::endl;
    }

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

    if (captchaMode) { runCaptcha(hConsole); }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << std::format("\nМатрица после удаления {} столбца:", K) << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < newN; ++j) {
            std::cout << matrix[i * newN + j] << "\t";
        }
        std::cout << std::endl;
    }

    delete[] matrix;

    SetConsoleTextAttribute(hConsole, oldColorAttrs);
    
    return 0;
}