#include "Task2Exercise.h"
#include <cmath>
#include <iostream>
#include <memory>

namespace miit::algebra
{

    Task2Exercise::Task2Exercise(Matrix<int> mat) : Exercise(std::move(mat))
    {
    }

    size_t Task2Exercise::count_even_digits_number() const
    {
        size_t count = 0;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            int first_digit = get_first_digit(matrix[i]);
            int last_digit = get_last_digit(matrix[i]);

            if (first_digit % 2 == 0 && last_digit % 2 == 0)
            {
                count++;
            }
        }
        return count;
    }

    int Task2Exercise::get_first_digit(int number) const
    {
        number = std::abs(number);
        while (number >= 10) {
            number /= 10;
        }
        return number;
    }

    int Task2Exercise::get_last_digit(int number) const
    {
        return std::abs(number) % 10;
    }

    void Task2Exercise::execute_task2()
    {
        size_t count_even = count_even_digits_number();
        size_t new_size = matrix.size() - count_even;

        if (new_size == 0) {
            std::cout << "Массив пустой после фильтрации." << std::endl;
            return;
        }

        std::unique_ptr<int[]> new_data = std::make_unique<int[]>(new_size);
        size_t index = 0;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            int first_digit = get_first_digit(matrix[i]);
            int last_digit = get_last_digit(matrix[i]);
            if (!(first_digit % 2 == 0 && last_digit % 2 == 0))
            {
                new_data[index++] = matrix[i];
            }
        }

        Matrix<int> result_matrix(new_data.get(), new_size);
        std::cout << "Массив после фильтрации: " << result_matrix.to_string() << std::endl;
    }

}
