#include "gtest/gtest.h"
#include "../Matrix/Task3Exercise.h"

namespace miit::algebra {

    TEST(Task3, ApplyTransformationRules) {
        Matrix<int> orig({ 1, 2, 3, 4 });
        Task3Exercise task(orig);
        task.execute_task3();
        const auto& res = task.get_matrix();
        EXPECT_EQ(res[0], 0);
        EXPECT_EQ(res[1], 1);
        EXPECT_EQ(res[2], -9);
        EXPECT_EQ(res[3], -15);
    }

}