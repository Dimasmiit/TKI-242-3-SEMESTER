#include "Task2Exercise.h"
#include <iostream>
#include <cmath>

namespace miit::algebra
{
    Task2Exercise::Task2Exercise(Matrix<int>& matrix, Generator& gen) : Exercise(matrix, gen)
    {
        std::cout << "Задание 2" << std::endl;
        matrix.fill(gen);
    }

    bool Task2Exercise::hasEvenFirstAndLastDigit(int number)
    {
        number = std::abs(number);
        
        int lastDigit = number % 10;
        
        int firstDigit = number;
        while (firstDigit >= 10) {
            firstDigit /= 10;
        }
        
        return (firstDigit % 2 == 0) && (lastDigit % 2 == 0);
    }

    size_t Task2Exercise::countElementsToRemove()
    {
        size_t count = 0;
        for (size_t i = 0; i < matrix.getSize(); i++) {
            if (hasEvenFirstAndLastDigit(matrix[i])) {
                count++;
            }
        }
        return count;
    }

    Matrix<int> Task2Exercise::createFilteredArray()
    {
        size_t elementsToRemove = countElementsToRemove();
        size_t newSize = matrix.getSize() - elementsToRemove;
        
        if (newSize == 0) {
            return Matrix<int>();
        }
        
        Matrix<int> result(newSize);
        size_t j = 0;
        
        for (size_t i = 0; i < matrix.getSize(); i++) {
            if (!hasEvenFirstAndLastDigit(matrix[i])) {
                result[j++] = matrix[i];
            }
        }
        
        return result;
    }

    void Task2Exercise::task()
    {
        std::cout << "Было: " << matrix.toString() << std::endl;
        
        Matrix<int> filtered = createFilteredArray();
        
        if (filtered.isEmpty()) {
            std::cout << "После удаления элементов с четными первой и последней цифрами: все элементы удалены" << std::endl;
        } else {
            std::cout << "После удаления элементов с четными первой и последней цифрами: " << filtered.toString() << std::endl;
        }
        std::cout << std::endl;
    }
}