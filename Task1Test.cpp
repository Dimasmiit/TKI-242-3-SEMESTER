#include "gtest/gtest.h"
#include "../Matrix/Task1Exercise.h"

namespace miit::algebra {

    TEST(Task1, ReplaceMinAbsPos) {
        Matrix<int> orig({ 5, -2, 3, 1 });
        Task1Exercise task(orig);
        task.execute_task1();
        EXPECT_EQ(task.get_matrix().to_string(), "[5, -2, 3, 0]");
    }

    TEST(Task1, NoPositives) {
        Matrix<int> orig({ -1, -2 });
        Task1Exercise task(orig);
        task.execute_task1();
        EXPECT_EQ(task.get_matrix().to_string(), "[-1, -2]");
    }

} 