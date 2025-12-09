#include "gtest/gtest.h"
#include "../Matrix/Matrix.h"
#include "../Matrix/IStreamGenerator.h"
#include <sstream>
#include <initializer_list>

namespace miit::algebra {

    TEST(ArrayDefaultCtor, CreatesEmpty) {
        Matrix<int> m;
        EXPECT_EQ(m.size(), 0);
        EXPECT_EQ(m.to_string(), "[]");
    }

    TEST(ArraySizeCtor, InitializesWithZeros) {
        Matrix<int> m(3);
        EXPECT_EQ(m.size(), 3);
        EXPECT_EQ(m[0], 0);
    }

    TEST(ArrayInitListCtor, FillsCorrectly) {
        Matrix<int> m({ 1, 2, 3 });
        EXPECT_EQ(m.to_string(), "[1, 2, 3]");
    }

    TEST(ArrayCopyCtor, ClonesData) {
        Matrix<int> orig({ 1, 2 });
        Matrix<int> copy(orig);
        EXPECT_EQ(copy.to_string(), "[1, 2]");
    }

    TEST(ArrayAssignOp, CopiesData) {
        Matrix<int> orig({ 3, 4 });
        Matrix<int> dest(1);
        dest = orig;
        EXPECT_EQ(dest.to_string(), "[3, 4]");
    }

    TEST(ArrayIndexOp, OutOfBoundsThrows) {
        Matrix<int> m(2);
        EXPECT_NO_THROW(m[0]);
        EXPECT_THROW(m[5], std::out_of_range);
    }

    TEST(ArrayFill, FromGenerator) {
        std::istringstream input("10 20");
        IStreamGenerator gen(input);
        Matrix<int> m(2);
        m.fill(gen);
        EXPECT_EQ(m.to_string(), "[10, 20]");
    }

}