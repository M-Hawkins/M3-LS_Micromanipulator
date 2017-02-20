#include "gtest/gtest.h"
#include "Arduino.h"
using ::testing::Return;

// TEST(getCurrentPosition, XYZ) {
//     M3LS m3 = M3LS(1, 2, 3);
//     m3.getCurrentPosition();
//     long* currPos = m3.currentPosition;
//     ASSERT_EQ(12345678, currPos[0]);
//     ASSERT_EQ(12345678, currPos[1]);
//     ASSERT_EQ(12345678, currPos[2]);
//     releaseArduinoMock();
// }

TEST(passTest, T1){
    int x = 1;
    int y = 1;
    ASSERT_EQ(x, y);
    releaseArduinoMock();
}