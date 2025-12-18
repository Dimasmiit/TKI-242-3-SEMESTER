#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Задание 2: Удаление элементов с четными первой и последней цифрами
     */
    class Task2Exercise : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task2Exercise
         * @param matrix Ссылка на объект класса Matrix
         * @param gen Ссылка на генератор для заполнения
         */
        Task2Exercise(Matrix<int>& matrix, Generator& gen);

        /**
         * @brief Реализация выполнения второго задания
         */
        void task() override;

    private:
        /**
         * @brief Проверить, четные ли первая и последняя цифры числа
         * @param number Число для проверки
         * @return true если обе цифры четные
         */
        bool hasEvenFirstAndLastDigit(int number);

        /**
         * @brief Подсчитать количество элементов для удаления
         * @return Количество элементов с четными первой и последней цифрами
         */
        size_t countElementsToRemove();

        /**
         * @brief Создать новый массив без элементов с четными первой и последней цифрами
         * @return Новый массив
         */
        Matrix<int> createFilteredArray();
    };
}