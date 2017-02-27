#include "gtest/gtest.h"
#include "M3LS.h"
using ::testing::Return;

namespace testing
{
 namespace internal
 {
  enum GTestColor {
      COLOR_DEFAULT,
      COLOR_RED,
      COLOR_GREEN,
      COLOR_YELLOW
  };

  extern void ColoredPrintf(GTestColor color, const char* fmt, ...);
 }
}
#define PRINTF(...)  do { testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[          ] "); testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, __VA_ARGS__); } while(0)

// C++ stream interface
class TestCout : public std::stringstream
{
public:
    ~TestCout()
    {
        PRINTF("%s",str().c_str());
    }
};

#define TEST_COUT  TestCout()

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

TEST(ControlMode, Set){
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
    ASSERT_EQ(M3LS::position, m3.currentControlMode);
    m3.setControlMode(M3LS::position);
    ASSERT_EQ(M3LS::position, m3.currentControlMode);
    m3.setControlMode(M3LS::velocity);
    ASSERT_EQ(M3LS::velocity, m3.currentControlMode);
    m3.setControlMode(M3LS::velocity);
    ASSERT_EQ(M3LS::velocity, m3.currentControlMode);
    m3.setControlMode(M3LS::position);
    ASSERT_EQ(M3LS::position, m3.currentControlMode);

    releaseArduinoMock();
}

TEST(UpdatePosition, X){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::X);
    ASSERT_EQ(targetPositionX, m3.currentPosition[0]);
    ASSERT_EQ(startingPositions[1], m3.currentPosition[1]);
    ASSERT_EQ(startingPositions[2], m3.currentPosition[2]);

    releaseArduinoMock();
}

TEST(UpdatePosition, Y){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::Y);
    ASSERT_EQ(startingPositions[0], m3.currentPosition[0]);
    ASSERT_EQ(targetPositionY, m3.currentPosition[1]);
    ASSERT_EQ(startingPositions[2], m3.currentPosition[2]);

    releaseArduinoMock();
}

TEST(UpdatePosition, Z){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::Z);
    ASSERT_EQ(startingPositions[0], m3.currentPosition[0]);
    ASSERT_EQ(startingPositions[1], m3.currentPosition[1]);
    ASSERT_EQ(targetPositionZ, m3.currentPosition[2]);

    releaseArduinoMock();
}

TEST(UpdatePosition, XY){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::XY);
    ASSERT_EQ(targetPositionX, m3.currentPosition[0]);
    ASSERT_EQ(targetPositionY, m3.currentPosition[1]);
    ASSERT_EQ(startingPositions[2], m3.currentPosition[2]);

    releaseArduinoMock();
}

TEST(UpdatePosition, XZ){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::XZ);
    ASSERT_EQ(targetPositionX, m3.currentPosition[0]);
    ASSERT_EQ(startingPositions[1], m3.currentPosition[1]);
    ASSERT_EQ(targetPositionZ, m3.currentPosition[2]);

    releaseArduinoMock();
}

TEST(UpdatePosition, YZ){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::YZ);
    ASSERT_EQ(startingPositions[0], m3.currentPosition[0]);
    ASSERT_EQ(targetPositionY, m3.currentPosition[1]);
    ASSERT_EQ(targetPositionZ, m3.currentPosition[2]);

    releaseArduinoMock();
}

TEST(UpdatePosition, XYZ){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::XYZ);
    ASSERT_EQ(targetPositionX, m3.currentPosition[0]);
    ASSERT_EQ(targetPositionY, m3.currentPosition[1]);
    ASSERT_EQ(targetPositionZ, m3.currentPosition[2]);

    m3.updatePosition(startingPositions[0], startingPositions[1], startingPositions[2]);
    ASSERT_EQ(startingPositions[0], m3.currentPosition[0]);
    ASSERT_EQ(startingPositions[1], m3.currentPosition[1]);
    ASSERT_EQ(startingPositions[2], m3.currentPosition[2]);

    releaseArduinoMock();
}

TEST(Home, Set){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::XYZ);
    m3.setHome();
    ASSERT_EQ(targetPositionX, m3.homePosition[0]);
    ASSERT_EQ(targetPositionY, m3.homePosition[1]);
    m3.updatePosition(startingPositions[0], startingPositions[1], startingPositions[2], M3LS::XYZ);
    ASSERT_EQ(targetPositionX, m3.homePosition[0]);
    ASSERT_EQ(targetPositionY, m3.homePosition[1]);

    releaseArduinoMock();
}

TEST(Home, Return){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
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
    m3.updatePosition(targetPositionX, targetPositionY, targetPositionZ, M3LS::XYZ);
    m3.setHome();
    m3.updatePosition(startingPositions[0], startingPositions[1], startingPositions[2], M3LS::XYZ);
    ASSERT_EQ(targetPositionX, m3.homePosition[0]);
    ASSERT_EQ(targetPositionY, m3.homePosition[1]);
    m3.returnHome();
    ASSERT_EQ(targetPositionX, m3.currentPosition[0]);
    ASSERT_EQ(targetPositionY, m3.currentPosition[1]);


    releaseArduinoMock();
}
