#include "gtest/gtest.h"
#include "../Matrix/Task2Exercise.h"

namespace miit::algebra {

    TEST(Task2, FilterEvenDigits) {
        Matrix<int> orig({ 24, 13, 68 });
        Task2Exercise task(orig);
        testing::internal::CaptureStdout();
        task.execute_task2();
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_TRUE(output.find("13") != std::string::npos);
        EXPECT_TRUE(output.find("24") == std::string::npos);
    }

    TEST(Task2, NoElementsAfterFilter) {
        Matrix<int> orig({ 24, 68 });
        Task2Exercise task(orig);
        testing::internal::CaptureStdout();
        task.execute_task2();
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_TRUE(output.find("Массив пустой") != std::string::npos);
    }

}