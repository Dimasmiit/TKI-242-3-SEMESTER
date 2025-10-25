#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Реализация первого задания
     */
    class Task1Exercise : public Exercise
    {
    public:
        /**
         * @brief Конструктор
         * @param mat Матрица для обработки
         */
        explicit Task1Exercise(Matrix<int> mat);

        /**
         * @brief Деструктор
         */
        ~Task1Exercise() override = default;

        /**
         * @brief Замена минимального по модулю положительного элемента нулем
         */
        void execute_task1();
    };
}
