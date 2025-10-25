#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra {
    /**
     * @brief Генератор случайных чисел в заданном диапазоне
     */
    class RandomGenerator : public Generator {
    private:
        std::uniform_int_distribution<int> value_distribution;
        std::mt19937 random_generator;

    public:
        /**
         * @brief Конструктор генератора случайных чисел
         * @param min Минимальное значение диапазона
         * @param max Максимальное значение диапазона
         */
        RandomGenerator(int min, int max);

        /**
         * @brief Генерирует случайное число в заданном диапазоне
         * @return Случайное целое число
         */
        int generate() override;

        /**
         * @brief Деструктор
         */
        ~RandomGenerator() override = default;
    };
}