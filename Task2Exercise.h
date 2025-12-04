#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Реализация второго задания
     */
    class Task2Exercise : public Exercise
    {
    private:
        /**
         * @brief Подсчитывает элементы с четными первой и последней цифрами
         * @return Количество таких элементов
         */
        size_t count_even_digits_number() const;

        /**
         * @brief Получает первую цифру числа
         * @param number Исходное число
         * @return Первая цифра
         */
        int get_first_digit(const int number) const;

        /**
         * @brief Получает последнюю цифру числа
         * @param number Исходное число
         * @return Последняя цифра
         */
        int get_last_digit(const int number) const;

    public:
        /**
         * @brief Конструктор
         * @param mat Матрица для обработки
         */
        explicit Task2Exercise(Matrix<int> mat);

        /**
         * @brief Деструктор
         */
        ~Task2Exercise() = default;

        /**
         * @brief Удаление элементов с четными первой и последней цифрами и вывод результата
         */
        void execute_task() override;
    };
}
