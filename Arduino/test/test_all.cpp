#define TESTING
#include "gtest/gtest.h"
#include "arduino-mock/Arduino.h"
#include "../src/M3LS/M3LS.h"
using ::testing::Return;

TEST(getCurrentPosition, XYZ) {
    M3LS m3 = M3LS(1, 2, 3);
    m3.getCurrentPosition();
    long* currPos = m3.currentPosition;
    ASSERT_EQ(12345678, currPos[0]);
    ASSERT_EQ(12345678, currPos[1]);
    ASSERT_EQ(12345678, currPos[2]);
    releaseArduinoMock();
}