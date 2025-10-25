#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
    /**
     * @brief Генератор значений из входного потока
     * @details Читает значения из указанного входного потока
     */
    class IStreamGenerator : public Generator
    {
    private:
        std::istream& in;

    public:
        /**
         * @brief Конструктор генератора из потока
         * @param input Ссылка на входной поток
         */
        explicit IStreamGenerator(std::istream& input);

        /**
         * @brief Читает следующее значение из потока
         * @return Прочитанное целое число
         */
        int generate() override;

        /**
         * @brief Деструктор
         */
        ~IStreamGenerator() override = default;
    };
}