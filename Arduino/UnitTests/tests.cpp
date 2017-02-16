#include <gtest/gtest.h>
 
TEST(SampleTest, PassTest) { 
    ASSERT_EQ(1, 1);
}
 
TEST(SampleTest, FailTest) {
    ASSERT_EQ(1, 2);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}