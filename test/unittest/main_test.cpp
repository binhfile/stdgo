/**
 * @author binhfile
 * @brief Main function for testcase
 */ 
#if defined(STDGO_UNITTEST) && defined(STDGO_UNITTEST_ALL)
#include <stdio.h>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  return ret;
}
#endif // STDGO_UNITTEST_ALL