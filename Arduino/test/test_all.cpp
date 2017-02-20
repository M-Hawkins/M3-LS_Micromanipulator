#include "gtest/gtest.h"
#include "M3LS.h"
using ::testing::Return;

TEST(Constructor, SingleAxis){
    // Initialize test parameters
    int pins[] = {1};
    int numAxes = 1;

    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS and execute functions to be tested
    M3LS m3 = M3LS(pins[0]);
    releaseArduinoMock();
}

TEST(Constructor, DoubleAxis){
    // Initialize test parameters
    int pins[] = {1, 2};
    int numAxes = 2;

    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS and execute functions to be tested
    M3LS m3 = M3LS(pins[0], pins[1]);
    releaseArduinoMock();
}

TEST(Constructor, TripleAxis){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
    int numAxes = 3;

    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS and execute functions to be tested
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    releaseArduinoMock();
}

TEST(getCurrentPosition, XYZ){
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