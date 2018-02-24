/**
 * @author binhfile
 * @brief Main function for testcase
 */
#if defined(GO_UNITTEST)
#include <gtest/gtest.h>
#include <stdio.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    return ret;
}
#endif // GO_UNITTEST