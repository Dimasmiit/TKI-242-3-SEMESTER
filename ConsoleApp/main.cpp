#include <iostream>
#include <memory>
#include "Task1Exercise.h"
#include "Task2Exercise.h"
#include "Task3Exercise.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"

using namespace miit::algebra;

enum class FillMethod {
    RANDOM = 1,
    MANUAL = 2,
    CONSTANT = 3
};

int main() {
    try {
        std::cout << "Введите размер массива: ";
        size_t n;
        std::cin >> n;
        
        if (n == 0) {
            std::cerr << "Размер массива должен быть больше 0\n";
            return EXIT_FAILURE;
        }

        if (n < 12) {
            std::cerr << "Внимание: для задания 3 требуется размер массива не менее 12\n";
        }

        std::cout << "\nВыберите способ заполнения массива:\n";
        std::cout << "  " << static_cast<int>(FillMethod::RANDOM) << " - Случайными числами\n";
        std::cout << "  " << static_cast<int>(FillMethod::MANUAL) << " - Вручную (ввод с клавиатуры)\n";
        std::cout << "  " << static_cast<int>(FillMethod::CONSTANT) << " - Константой (одно и то же число)\n";
        std::cout << "Ваш выбор: ";
        
        int choice;
        std::cin >> choice;

        std::unique_ptr<Generator> gen;
        
        switch (static_cast<FillMethod>(choice)) {
            case FillMethod::RANDOM: {
                std::cout << "\nВведите минимальное значение: ";
                int min;
                std::cin >> min;
                std::cout << "Введите максимальное значение: ";
                int max;
                std::cin >> max;
                
                if (min > max) {
                    std::cerr << "Минимум не может быть больше максимума!\n";
                    return EXIT_FAILURE;
                }
                
                gen = std::make_unique<RandomGenerator>(min, max);
                break;
            }
            case FillMethod::MANUAL: {
                std::cout << "\nВы выбрали ввод вручную.\n";
                std::cout << "При заполнении массива введите " << n << " чисел.\n";
                gen = std::make_unique<IStreamGenerator>(std::cin);
                break;
            }
            case FillMethod::CONSTANT: {
                std::cout << "\nВведите константу для заполнения: ";
                int constant;
                std::cin >> constant;
                gen = std::make_unique<ConstantGenerator>(constant);
                break;
            }
            default:
                std::cerr << "Неверный выбор\n";
                return EXIT_FAILURE;
        }
        std::cout << "\n";

        {
            Matrix<int> arr1(n);
            Task1Exercise task1(arr1, *gen);
            task1.task();
        }
        
        {
            Matrix<int> arr2(n);
            Task2Exercise task2(arr2, *gen);
            task2.task();
        }

        if (n >= 12) {
            Matrix<int> arr3(n);
            Task3Exercise task3(arr3, *gen);
            task3.task();
        } else {
            std::cout << "Задание 3 пропущено (требуется размер >= 12)\n\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}