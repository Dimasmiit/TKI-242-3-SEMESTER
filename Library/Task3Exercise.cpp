#include "Task3Exercise.h"
#include <iostream>

namespace miit::algebra
{
    Task3Exercise::Task3Exercise(Matrix<int>& matrix, Generator& gen) 
        : Exercise(matrix, gen)
    {
        if (matrix.getSize() < 12) {
            throw std::invalid_argument("Размер массива должен быть не менее 12 для выполнения задания 3");
        }
        std::cout << "Задание 3" << std::endl;
        matrix.fill(gen);
    }

    Matrix<int> Task3Exercise::createArrayA()
    {
        size_t size = matrix.getSize();
        Matrix<int> A(size);

        for (size_t i = 0; i < size; i++) {
            if (i >= 2 && i <= 11) {
                A[i] = -1 * (matrix[i] * matrix[i]);
            } else {
                A[i] = matrix[i] - 1;
            }
        }

        return A;
    }

    void Task3Exercise::task()
    {
        std::cout << "Было: " << matrix.toString() << std::endl;
        
        Matrix<int> A = createArrayA();
        
        std::cout << "После формирования массива A по правилу: " << A.toString() << std::endl << std::endl;
    }
}