#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание 3: Формирование массива A по правилу
     */
    class Task3Exercise : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task3Exercise
         * @param matrix Ссылка на объект класса Matrix
         * @param gen Ссылка на генератор для заполнения
         */
        Task3Exercise(Matrix<int>& matrix, Generator& gen);

        /**
         * @brief Реализация выполнения третьего задания
         */
        void task() override;

    private:
        /**
         * @brief Создать массив A по правилу
         * @return Новый массив A
         */
        Matrix<int> createArrayA();
    };
}