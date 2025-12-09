#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание 1: Замена минимального по модулю положительного элемента на 0
     */
    class Task1Exercise : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task1Exercise
         * @param matrix Ссылка на объект класса Matrix
         * @param gen Ссылка на генератор для заполнения
         */
        Task1Exercise(Matrix<int>& matrix, Generator& gen);

        /**
         * @brief Реализация выполнения первого задания
         */
        void task() override;

    private:
        /**
         * @brief Найти индекс минимального по модулю положительного элемента
         * @return Индекс найденного элемента или -1, если не найден
         */
        int findMinPositiveIndex();
    };
}