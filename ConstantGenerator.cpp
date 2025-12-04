#include "ConstantGenerator.h"

namespace miit::algebra
{
        ConstantGenerator::ConstantGenerator(int value)
        : value{value}  // Инициализируем поле value переданным параметром
    {
    }
    int ConstantGenerator::generate()
    {
        return value;
    }
}