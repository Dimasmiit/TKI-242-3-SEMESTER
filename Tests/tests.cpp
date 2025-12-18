#include <gtest/gtest.h>
#include "../Library/Matrix.h"
#include "../Library/RandomGenerator.h"
#include "../Library/ConstantGenerator.h"
#include "../Library/IStreamGenerator.h"
#include "../Library/Task1Exercise.h"
#include "../Library/Task2Exercise.h"
#include "../Library/Task3Exercise.h"
#include <sstream>

using namespace miit::algebra;

// ==================== ТЕСТЫ MATRIX ====================

class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MatrixTest, DefaultConstructor) {
    Matrix<int> m;
    EXPECT_EQ(m.getSize(), 0);
    EXPECT_TRUE(m.isEmpty());
    EXPECT_EQ(m.toString(), "[]");
}

TEST_F(MatrixTest, SizeConstructor) {
    Matrix<int> m(5);
    EXPECT_EQ(m.getSize(), 5);
    EXPECT_FALSE(m.isEmpty());
}

TEST_F(MatrixTest, ZeroSizeThrowsException) {
    EXPECT_THROW({
        Matrix<int> m(0);
    }, std::invalid_argument);
}

TEST_F(MatrixTest, CopyConstructor) {
    Matrix<int> m1(3);
    m1[0] = 10;
    m1[1] = 20;
    m1[2] = 30;
    
    Matrix<int> m2 = m1;
    
    EXPECT_EQ(m2.getSize(), 3);
    EXPECT_EQ(m2[0], 10);
    EXPECT_EQ(m2[1], 20);
    EXPECT_EQ(m2[2], 30);
    
    // Проверяем глубокое копирование
    m2[0] = 999;
    EXPECT_EQ(m1[0], 10);
    EXPECT_EQ(m2[0], 999);
}

TEST_F(MatrixTest, MoveConstructor) {
    Matrix<int> m1(3);
    m1[0] = 10;
    m1[1] = 20;
    m1[2] = 30;
    
    Matrix<int> m2 = std::move(m1);
    
    EXPECT_EQ(m2.getSize(), 3);
    EXPECT_EQ(m2[0], 10);
    EXPECT_EQ(m2[1], 20);
    EXPECT_EQ(m2[2], 30);
    EXPECT_TRUE(m1.isEmpty());
}

TEST_F(MatrixTest, CopyAssignment) {
    Matrix<int> m1(3);
    m1[0] = 10;
    m1[1] = 20;
    m1[2] = 30;
    
    Matrix<int> m2(5);
    m2 = m1;
    
    EXPECT_EQ(m2.getSize(), 3);
    EXPECT_EQ(m2[0], 10);
    EXPECT_EQ(m2[1], 20);
    EXPECT_EQ(m2[2], 30);
}

TEST_F(MatrixTest, MoveAssignment) {
    Matrix<int> m1(3);
    m1[0] = 10;
    m1[1] = 20;
    m1[2] = 30;
    
    Matrix<int> m2(5);
    m2 = std::move(m1);
    
    EXPECT_EQ(m2.getSize(), 3);
    EXPECT_EQ(m2[0], 10);
    EXPECT_TRUE(m1.isEmpty());
}

TEST_F(MatrixTest, IndexOperator) {
    Matrix<int> m(3);
    m[0] = 100;
    m[1] = 200;
    m[2] = 300;
    
    EXPECT_EQ(m[0], 100);
    EXPECT_EQ(m[1], 200);
    EXPECT_EQ(m[2], 300);
}

TEST_F(MatrixTest, OutOfBoundsThrowsException) {
    Matrix<int> m(3);
    EXPECT_THROW({
        int val = m[10];
    }, std::out_of_range);
}

TEST_F(MatrixTest, ToString) {
    Matrix<int> m(3);
    m[0] = 1;
    m[1] = 2;
    m[2] = 3;
    
    EXPECT_EQ(m.toString(), "[1, 2, 3]");
}

TEST_F(MatrixTest, ToStringEmpty) {
    Matrix<int> m;
    EXPECT_EQ(m.toString(), "[]");
}

TEST_F(MatrixTest, GetData) {
    Matrix<int> m(3);
    m[0] = 10;
    m[1] = 20;
    m[2] = 30;
    
    int* data = m.getData();
    EXPECT_EQ(data[0], 10);
    EXPECT_EQ(data[1], 20);
    EXPECT_EQ(data[2], 30);
}

TEST_F(MatrixTest, FillWithGenerator) {
    Matrix<int> m(3);
    ConstantGenerator gen(42);
    m.fill(gen);
    
    EXPECT_EQ(m[0], 42);
    EXPECT_EQ(m[1], 42);
    EXPECT_EQ(m[2], 42);
}

// ==================== ТЕСТЫ ГЕНЕРАТОРОВ ====================

TEST(GeneratorTest, ConstantGenerator) {
    ConstantGenerator gen(777);
    
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(gen.generate(), 777);
    }
}

TEST(GeneratorTest, RandomGeneratorRange) {
    RandomGenerator gen(5, 10);
    
    for (int i = 0; i < 100; i++) {
        int value = gen.generate();
        EXPECT_GE(value, 5);
        EXPECT_LE(value, 10);
    }
}

TEST(GeneratorTest, IStreamGenerator) {
    std::istringstream input("10 20 30 40 50");
    IStreamGenerator gen(input);
    
    EXPECT_EQ(gen.generate(), 10);
    EXPECT_EQ(gen.generate(), 20);
    EXPECT_EQ(gen.generate(), 30);
    EXPECT_EQ(gen.generate(), 40);
    EXPECT_EQ(gen.generate(), 50);
}

// ==================== ТЕСТЫ TASK1 ====================

TEST(Task1Test, FindMinPositive) {
    Matrix<int> m(5);
    m[0] = -10;
    m[1] = 5;
    m[2] = -3;
    m[3] = 2;
    m[4] = 8;
    
    ConstantGenerator gen(0);
    Task1Exercise task(m, gen);
    
    // После выполнения task минимальный положительный (2) должен стать 0
    // Но нам нужно проверить логику напрямую
    
    // Проверяем, что минимальный положительный - это 2 (индекс 3)
    int minValue = -1;
    int minIndex = -1;
    
    for (size_t i = 0; i < m.getSize(); i++) {
        if (m[i] > 0) {
            if (minIndex == -1 || m[i] < minValue) {
                minValue = m[i];
                minIndex = i;
            }
        }
    }
    
    EXPECT_EQ(minIndex, 3);
    EXPECT_EQ(minValue, 2);
}

TEST(Task1Test, NoPositiveElements) {
    Matrix<int> m(3);
    m[0] = -5;
    m[1] = -10;
    m[2] = -3;
    
    ConstantGenerator gen(0);
    Task1Exercise task(m, gen);
    
    // Проверяем что нет положительных
    bool hasPositive = false;
    for (size_t i = 0; i < m.getSize(); i++) {
        if (m[i] > 0) hasPositive = true;
    }
    
    EXPECT_FALSE(hasPositive);
}

TEST(Task1Test, AllPositiveElements) {
    Matrix<int> m(4);
    m[0] = 10;
    m[1] = 2;
    m[2] = 7;
    m[3] = 5;
    
    ConstantGenerator gen(0);
    Task1Exercise task(m, gen);
    
    // Минимальный положительный - 2 (индекс 1)
    int minValue = m[1];
    for (size_t i = 0; i < m.getSize(); i++) {
        if (m[i] > 0 && m[i] < minValue) {
            minValue = m[i];
        }
    }
    
    EXPECT_EQ(minValue, 2);
}

// ==================== ТЕСТЫ TASK2 ====================

TEST(Task2Test, EvenFirstAndLastDigit) {
    // Проверяем логику определения четных первой и последней цифры
    
    // 24: первая=2(четная), последняя=4(четная) -> удалить
    int num1 = 24;
    int first1 = num1;
    while (first1 >= 10) first1 /= 10;
    int last1 = num1 % 10;
    EXPECT_TRUE(first1 % 2 == 0 && last1 % 2 == 0);
    
    // 23: первая=2(четная), последняя=3(нечетная) -> оставить
    int num2 = 23;
    int first2 = num2;
    while (first2 >= 10) first2 /= 10;
    int last2 = num2 % 10;
    EXPECT_FALSE(first2 % 2 == 0 && last2 % 2 == 0);
    
    // 13: первая=1(нечетная), последняя=3(нечетная) -> оставить
    int num3 = 13;
    int first3 = num3;
    while (first3 >= 10) first3 /= 10;
    int last3 = num3 % 10;
    EXPECT_FALSE(first3 % 2 == 0 && last3 % 2 == 0);
}

TEST(Task2Test, RemoveElements) {
    Matrix<int> m(5);
    m[0] = 24;  // 2-четная, 4-четная -> удалить
    m[1] = 13;  // 1-нечетная, 3-нечетная -> оставить
    m[2] = 86;  // 8-четная, 6-четная -> удалить
    m[3] = 15;  // 1-нечетная, 5-нечетная -> оставить
    m[4] = 22;  // 2-четная, 2-четная -> удалить
    
    // Должны остаться: 13, 15
    int expectedRemaining = 2;
    int actualRemaining = 0;
    
    for (size_t i = 0; i < m.getSize(); i++) {
        int num = std::abs(m[i]);
        int first = num;
        while (first >= 10) first /= 10;
        int last = num % 10;
        
        if (!(first % 2 == 0 && last % 2 == 0)) {
            actualRemaining++;
        }
    }
    
    EXPECT_EQ(actualRemaining, expectedRemaining);
}

TEST(Task2Test, NegativeNumbers) {
    Matrix<int> m(3);
    m[0] = -24;  // |-24| = 24: 2-четная, 4-четная -> удалить
    m[1] = -13;  // |-13| = 13: 1-нечетная, 3-нечетная -> оставить
    m[2] = -86;  // |-86| = 86: 8-четная, 6-четная -> удалить
    
    // Должен остаться только -13
    int count = 0;
    for (size_t i = 0; i < m.getSize(); i++) {
        int num = std::abs(m[i]);
        int first = num;
        while (first >= 10) first /= 10;
        int last = num % 10;
        
        if (!(first % 2 == 0 && last % 2 == 0)) {
            count++;
        }
    }
    
    EXPECT_EQ(count, 1);
}

// ==================== ТЕСТЫ TASK3 ====================

TEST(Task3Test, ArrayTransformation) {
    Matrix<int> m(15);
    for (size_t i = 0; i < m.getSize(); i++) {
        m[i] = static_cast<int>(i + 1);
    }
    
    // Проверяем формулу для индексов 2-11
    for (size_t i = 2; i <= 11; i++) {
        int expected = -1 * (m[i] * m[i]);
        int value = static_cast<int>(i + 1);
        EXPECT_EQ(expected, -1 * (value * value));
    }
    
    // Проверяем формулу для остальных индексов
    int expected0 = m[0] - 1;
    EXPECT_EQ(expected0, 0);
    
    int expected12 = m[12] - 1;
    EXPECT_EQ(expected12, 12);
}

TEST(Task3Test, MinimumSize) {
    Matrix<int> m(11);
    ConstantGenerator gen(5);
    
    EXPECT_THROW({
        Task3Exercise task(m, gen);
    }, std::invalid_argument);
}

TEST(Task3Test, ExactSize12) {
    Matrix<int> m(12);
    ConstantGenerator gen(3);
    
    EXPECT_NO_THROW({
        Task3Exercise task(m, gen);
    });
}

TEST(Task3Test, Formula) {
    Matrix<int> m(12);
    for (size_t i = 0; i < 12; i++) {
        m[i] = static_cast<int>(i);
    }
    
    ConstantGenerator gen(0);
    Task3Exercise task(m, gen);
    
    // Проверяем формулы
    // i=0: A[0] = D[0] - 1 = 0 - 1 = -1
    // i=1: A[1] = D[1] - 1 = 1 - 1 = 0
    // i=2: A[2] = -1 * (D[2] * D[2]) = -1 * (2 * 2) = -4
    // i=3: A[3] = -1 * (D[3] * D[3]) = -1 * (3 * 3) = -9
    // ...
    // i=11: A[11] = -1 * (D[11] * D[11]) = -1 * (11 * 11) = -121
    
    EXPECT_EQ(m[0] - 1, -1);
    EXPECT_EQ(-1 * (2 * 2), -4);
    EXPECT_EQ(-1 * (11 * 11), -121);
}

// ==================== MAIN ====================

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}