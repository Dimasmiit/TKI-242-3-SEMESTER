#include "gtest/gtest.h"
#include "../Matrix/RandomGenerator.h"
#include "../Matrix/IStreamGenerator.h"
#include <sstream>

namespace miit::algebra {

    TEST(RandomGen, ProducesInRange) {
        RandomGenerator gen(1, 3);
        for (int i = 0; i < 10; ++i) {
            int val = gen.generate();
            EXPECT_GE(val, 1);
            EXPECT_LE(val, 3);
        }
    }

    TEST(StreamGen, ReadsValues) {
        std::istringstream input("5 -1");
        IStreamGenerator gen(input);
        EXPECT_EQ(gen.generate(), 5);
        EXPECT_EQ(gen.generate(), -1);
    }

} 