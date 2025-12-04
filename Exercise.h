#pragma once

#include "Matrix.h"
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Абстрактный класс для выполнения заданий
     */
    class Exercise
    {
    protected:
        Matrix<int>& matrix;
        Generator& gen;

    public:
        /**
         * @brief Конструктор класса
         * @param matrix Ссылка на объект Matrix
         * @param gen Ссылка на генератор
         */
        Exercise(Matrix<int>& matrix, Generator& gen);

        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Exercise() = default;

        /**
         * @brief Виртуальная функция для решения задачи
         */
        virtual void task() = 0;
    };
}