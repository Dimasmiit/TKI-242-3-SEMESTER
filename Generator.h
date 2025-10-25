#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный базовый класс для генерации значений
     * @details Определяет интерфейс для всех генераторов значений
     */
    class Generator
    {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Generator() = default;

        /**
         * @brief Генерирует следующее значение
         * @return Сгенерированное целое число
         */
        virtual int generate() = 0;
    };
}