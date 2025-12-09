#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, возвращающий константное значение
     */
    class ConstantGenerator : public Generator
    {
    private:
        int value; 

    public:
        /**
         * @brief Конструктор
         * @param value Значение, которое будет возвращаться при каждом вызове generate()
         */
        ConstantGenerator(int value);

        /**
         * @brief Возвращает константное значение
         * @return Всегда одно и то же число
         */
        int generate() override;
    };
}