#include "gtest/gtest.h"
#include "M3LS.h"
using ::testing::Return;

TEST(getCurrentPosition, XYZ) {
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    EXPECT_CALL(*arduinoMock, pinMode(1, OUTPUT));
    EXPECT_CALL(*arduinoMock, digitalWrite(1, HIGH));

    // Initialize M3LS and execute functions to be tested
    M3LS m3 = M3LS(1);
    m3.getCurrentPosition();
    long* currPos = m3.currentPosition;

    // Check return values against expected
    ASSERT_EQ(0, currPos[0]);
    // ASSERT_EQ(12345678, currPos[1]);
    // ASSERT_EQ(12345678, currPos[2]);
    releaseArduinoMock();
}