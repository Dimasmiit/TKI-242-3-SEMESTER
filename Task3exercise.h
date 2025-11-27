#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Реализация третьего задания
     * @details Формирует массив A по специальным правилам
     */
    class Task3Exercise : public Exercise
    {
    public:
        /**
         * @brief Конструктор
         * @param mat Матрица для обработки
         */
        explicit Task3Exercise(Matrix<int> mat);

        /**
         * @brief Деструктор
         */
        ~Task3Exercise() override = default;

        /**
         * @brief Формирование массива A по правилам и вывод результата
         */
        void execute_task() override;
    };
}
