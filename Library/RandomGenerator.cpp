#include "RandomGenerator.h"

namespace miit::algebra {

    RandomGenerator::RandomGenerator(int min, int max)
        : random_generator(std::random_device{}()), value_distribution(min, max) {}

    int RandomGenerator::generate() {
        return value_distribution(random_generator);
    }

}