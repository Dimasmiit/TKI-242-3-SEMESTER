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

    int Task1Exercise::findFirstPositiveIndex() const
    {
        for (size_t i = 0; i < matrix.getSize(); i++) {
            if (matrix[i] > 0) {
                return static_cast<int>(i);
            }
        }
        return NOT_FOUND;
    }

    int Task1Exercise::findMinPositiveIndex() const
    {
        const int firstPositiveIndex = findFirstPositiveIndex();
        
        if (firstPositiveIndex == NOT_FOUND) {
            return NOT_FOUND;
        }

        int minIndex = firstPositiveIndex;
        int minValue = std::abs(matrix[firstPositiveIndex]);

        for (size_t i = static_cast<size_t>(firstPositiveIndex) + 1; i < matrix.getSize(); i++) {
            if (matrix[i] > 0) {
                const int absValue = std::abs(matrix[i]);
                if (absValue < minValue) {
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

        const int index = findMinPositiveIndex();

        if (index == NOT_FOUND) {
            std::cout << "После замены: Минимальный по модулю положительный элемент не найден" << std::endl;
            return;
        }

        matrix[index] = REPLACEMENT_VALUE;
        std::cout << "После замены минимального по модулю положительного элемента на 0: " 
                  << matrix.toString() << std::endl << std::endl;
    }
}