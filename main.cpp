#include <iostream>
#include <locale.h>
#include <memory>
#include "Task1Exercise.h"
#include "Task2Exercise.h"
#include "Task3Exercise.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"

using namespace miit::algebra;

int main() {
    setlocale(LC_ALL, "RUSSIAN");

    try {
        std::cout << "Введите размер массива: ";
        size_t size;
        std::cin >> size;

        if (size <= 0)
        {
            std::cerr << "Размер массива должен быть строго больше нуля" << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "Как вы хотите заполнить массив?" << std::endl;
        std::cout << "0 - Ручной ввод" << std::endl;
        std::cout << "1 - Заполнение массива случайными числами" << std::endl;

        int choice;
        std::cin >> choice;

        std::unique_ptr<Generator> generator;

        if (choice == 0)
        {
            std::cout << "Введите " << size << " элементов массива:" << std::endl;
            generator = std::make_unique<IStreamGenerator>(std::cin);
        }
        else if (choice == 1)
        {
            generator = std::make_unique<RandomGenerator>(-40, 40);
        }
        else
        {
            std::cerr << "Введено некорректное значение выбора" << std::endl;
            return EXIT_FAILURE;
        }

        Matrix<int> original_matrix(size);
        original_matrix.fill(*generator);

        std::cout << "Исходный массив:" << std::endl;
        std::cout << original_matrix.to_string() << std::endl;

        {
            Task1Exercise task1_exercise(original_matrix);
            task1_exercise.execute_task1();
            std::cout << "Массив, в котором минимальный по модулю положительный элемент заменен нулем:" << std::endl;
            std::cout << task1_exercise.get_matrix().to_string() << std::endl;
        }

        {
            Task2Exercise task2_exercise(original_matrix);
            std::cout << "Массив без элементов, у которых первая и последняя цифра четные:" << std::endl;
            task2_exercise.execute_task2(); // Вывод происходит внутри метода
        }

        {
            Task3Exercise task3_exercise(original_matrix);
            std::cout << "Массив A, сформированный из исходного массива по правилам:" << std::endl;
            task3_exercise.execute_task3(); // Вывод происходит внутри метода
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
