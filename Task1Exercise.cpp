#include "Task1Exercise.h"
#include <cmath>
#include <limits>

namespace miit::algebra
{

    Task1Exercise::Task1Exercise(Matrix<int> mat) : Exercise(std::move(mat))
    {
    }

    void Task1Exercise::execute_task1()
    {
        int min_abs_value = std::numeric_limits<int>::max();
        size_t min_index = static_cast<size_t>(-1);

        for (size_t i = 0; i < matrix.size(); ++i)
        {
            if (matrix[i] > 0)
            {
                int abs_value = std::abs(matrix[i]);
                if (abs_value < min_abs_value)
                {
                    min_abs_value = abs_value;
                    min_index = i;
                }
            }
        }

        if (min_index != static_cast<size_t>(-1))
        {
            matrix[min_index] = 0;
        }
    }

}