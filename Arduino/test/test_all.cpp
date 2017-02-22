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

TEST(GetCurrentPosition, X){
    // Initialize test parameters and call test function
    int pins[1] = {1};
    int numAxes = 1;
    long startingPositions[1] = {11111234L};
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    long* currPos = m3.getCurrentPosition();
    for (int pin = 0; pin < numAxes; pin++){
        ASSERT_EQ(startingPositions[pin], currPos[pin]);
    }
    releaseArduinoMock();
}

TEST(GetCurrentPosition, XY){
    // Initialize test parameters and call test function
    int pins[2] = {1, 2};
    int numAxes = 2;
    long startingPositions[2] = {11111234L, 22221234L};
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    long* currPos = m3.getCurrentPosition();
    for (int pin = 0; pin < numAxes; pin++){
        ASSERT_EQ(startingPositions[pin], currPos[pin]);
    }
    releaseArduinoMock();
}

TEST(GetCurrentPosition, XYZ){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    long* currPos = m3.getCurrentPosition();
    for (int pin = 0; pin < numAxes; pin++){
        ASSERT_EQ(startingPositions[pin], currPos[pin]);
    }
    releaseArduinoMock();
}

TEST(MoveToTargetPosition, X){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    long targetPositionX = 12344444L;
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    m3.moveToTargetPositionX(targetPositionX);
    long* currPos = m3.getCurrentPosition();
    ASSERT_EQ(targetPositionX, currPos[0]);
    ASSERT_EQ(startingPositions[1], currPos[1]);
    ASSERT_EQ(startingPositions[2], currPos[2]);

    // Execute default function and check return values against expected
    m3.moveToTargetPosition(startingPositions[0]);
    currPos = m3.getCurrentPosition();
    ASSERT_EQ(startingPositions[0], currPos[0]);
    ASSERT_EQ(startingPositions[1], currPos[1]);
    ASSERT_EQ(startingPositions[2], currPos[2]);

    releaseArduinoMock();
}

TEST(MoveToTargetPosition, Y){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    long targetPositionY = 12345555L;
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    m3.moveToTargetPositionY(targetPositionY);
    long* currPos = m3.getCurrentPosition();
    ASSERT_EQ(startingPositions[0], currPos[0]);
    ASSERT_EQ(targetPositionY, currPos[1]);
    ASSERT_EQ(startingPositions[2], currPos[2]);

    releaseArduinoMock();
}

TEST(MoveToTargetPosition, Z){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    long targetPositionZ = 12346666L;
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    m3.moveToTargetPositionZ(targetPositionZ);
    long* currPos = m3.getCurrentPosition();
    ASSERT_EQ(startingPositions[0], currPos[0]);
    ASSERT_EQ(startingPositions[1], currPos[1]);
    ASSERT_EQ(targetPositionZ, currPos[2]);

    releaseArduinoMock();
}

TEST(MoveToTargetPosition, XY){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    long targetPositionX = 12344444L;
    long targetPositionY = 12345555L;
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    m3.moveToTargetPositionXY(targetPositionX, targetPositionY);
    long* currPos = m3.getCurrentPosition();
    ASSERT_EQ(targetPositionX, currPos[0]);
    ASSERT_EQ(targetPositionY, currPos[1]);
    ASSERT_EQ(startingPositions[2], currPos[2]);

    // Execute default function and check return values against expected
    m3.moveToTargetPosition(startingPositions[0], startingPositions[1]);
    currPos = m3.getCurrentPosition();
    ASSERT_EQ(startingPositions[0], currPos[0]);
    ASSERT_EQ(startingPositions[1], currPos[1]);
    ASSERT_EQ(startingPositions[2], currPos[2]);

    releaseArduinoMock();
}

TEST(MoveToTargetPosition, XZ){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    long targetPositionX = 12344444L;
    long targetPositionZ = 12346666L;
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    m3.moveToTargetPositionXZ(targetPositionX, targetPositionZ);
    long* currPos = m3.getCurrentPosition();
    ASSERT_EQ(targetPositionX, currPos[0]);
    ASSERT_EQ(startingPositions[1], currPos[1]);
    ASSERT_EQ(targetPositionZ, currPos[2]);

    releaseArduinoMock();
}

TEST(MoveToTargetPosition, YZ){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    long targetPositionY = 12345555L;
    long targetPositionZ = 12346666L;
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    m3.moveToTargetPositionYZ(targetPositionY, targetPositionZ);
    long* currPos = m3.getCurrentPosition();
    ASSERT_EQ(startingPositions[0], currPos[0]);
    ASSERT_EQ(targetPositionY, currPos[1]);
    ASSERT_EQ(targetPositionZ, currPos[2]);

    releaseArduinoMock();
}

TEST(MoveToTargetPosition, XYZ){
    // Initialize test parameters and call test function
    int pins[3] = {1, 2, 3};
    int numAxes = 3;
    long startingPositions[3] = {11111234L, 22221234L, 33331234L};
    long targetPositionX = 12344444L;
    long targetPositionY = 12345555L;
    long targetPositionZ = 12346666L;
    
    // Initialize mock Arduino instance and expected calls
    ArduinoMock* arduinoMock = arduinoMockInstance();
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }

    // Initialize M3LS with starting positions
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);
    for (int pin = 0; pin < numAxes; pin++){
        m3.currentPosition[pin] = startingPositions[pin];
    }

    // Execute function and check return values against expected
    m3.moveToTargetPositionXYZ(targetPositionX, targetPositionY, targetPositionZ);
    long* currPos = m3.getCurrentPosition();
    ASSERT_EQ(targetPositionX, currPos[0]);
    ASSERT_EQ(targetPositionY, currPos[1]);
    ASSERT_EQ(targetPositionZ, currPos[2]);

    // Execute default function and check return values against expected
    m3.moveToTargetPosition(startingPositions[0], startingPositions[1], startingPositions[2]);
    currPos = m3.getCurrentPosition();
    ASSERT_EQ(startingPositions[0], currPos[0]);
    ASSERT_EQ(startingPositions[1], currPos[1]);
    ASSERT_EQ(startingPositions[2], currPos[2]);

    releaseArduinoMock();
}