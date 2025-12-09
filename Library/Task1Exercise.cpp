#include "Task1Exercise.h"
#include <iostream>
#include <cmath>

namespace miit::algebra
{
    Task1Exercise::Task1Exercise(Matrix<int>& matrix, Generator& gen) 
        : Exercise(matrix, gen)
    {
        std::cout << "Задание 1" << std::endl << std::endl;
        matrix.fill(gen);
    }

    int Task1Exercise::findMinPositiveIndex()
    {
        int minIndex = -1;
        int minValue = -1;

        for (size_t i = 0; i < matrix.getSize(); i++) {
            if (matrix[i] > 0) {
                int absValue = std::abs(matrix[i]);
                if (minIndex == -1 || absValue < minValue) {
                    minValue = absValue;
                    minIndex = static_cast<int>(i);
                }
            }
        }

        return minIndex;
    }

    void Task1Exercise::task()
    {
        std::cout << "Было: " << matrix.toString() << std::endl;

        int index = findMinPositiveIndex();

        if (index == -1) {
            std::cout << "После замены: Минимальный по модулю положительный элемент не найден" << std::endl;
            return;
        }

        matrix[index] = 0;
        std::cout << "После замены минимального по модулю положительного элемента на 0: " 
                  << matrix.toString() << std::endl << std::endl;
    }
}