#include <gtest/gtest.h>
#include "../M3LS.h"
 
TEST(getCurrentPosition, XYZ) {
    m3.getCurrentPosition();
    long currPos[3] = m3.currentPosition;
    ASSERT_EQ(12345678, currPos[0]);
    ASSERT_EQ(12345678, currPos[1]);
    ASSERT_EQ(12345678, currPos[2]);
}
 
int main(int argc, char **argv) {
    M3LS m3 = M3LS(1, 2, 3);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}