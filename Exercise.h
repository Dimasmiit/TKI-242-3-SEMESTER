#include "Task3Exercise.h"
#include <cmath>
#include <iostream>

namespace miit::algebra
{

    Task3Exercise::Task3Exercise(Matrix<int> mat) : Exercise(std::move(mat))
    {
    }

    void Task3Exercise::execute_task3()
    {
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            if (i >= 2 && i <= 11)
            {
                matrix[i] = -matrix[i] * matrix[i];
            }
            else
            {
                matrix[i] = matrix[i] - 1;
            }
        }
        std::cout << "Массив A (после преобразований): " << matrix.to_string() << std::endl;
    }

}
