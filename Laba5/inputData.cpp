#include "validation.h"
#include "inputData.h"
#include <regex>
#include <stdexcept>
#include <iostream>
#include <Windows.h>

double getInput(const std::string& inputType) {

	while (true) {

		std::cout << inputMsg(inputType);
		std::string input;
		if (!std::getline(std::cin, input))
		{
			std::exit(0);
		}

		std::string validResult = returnValidation(input);


		if (validResult != "Valid") {
			std::cout << validResult << std::endl << std::endl;
			continue;
		}

		std::cout << "\n";

		int res = std::stoi(input);

		if (inputType == "N" && res <= 0) {
			std::cout << "Уважаемый пользователь, спешим вам напомнить, что матрицы с отрицательным размером или 0x0 не существует. @Team_Autism™ 2026. All Rights Reserved." << std::endl << std::endl;
			continue;
		}
		if (inputType == "N" && res > 250) {
			std::cout << "Уважаемый пользователь, введенная вами размерность матрицы слишком велика, давайте не будем использовать матрицу размером более чем 250x250. @Team_Autism™ 2026. All Rights Reserved." << std::endl << std::endl;
			continue;
		}
		if (inputType == "K" && res < 1) {
			std::cout << "Уважаемый пользователь, спешим вам напомнить, что в матрице нумерация столбцов начинается с j=1. @Team_Autism™ 2026. All Rights Reserved." << std::endl << std::endl;
			continue;
		}

		return res;
	}
}

std::string inputMsg(const std::string& inputType) {
	if (inputType == "N") {
		return "Введите размерность N квадратной матрицы: ";
	}
	if (inputType == "K") {
		return "Введите, какой столбец K требуется удалить: ";
	}
	return "Неизвестный тип параметра";
}