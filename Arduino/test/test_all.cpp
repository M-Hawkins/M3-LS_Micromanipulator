#include "gtest/gtest.h"
#include "M3LS.h"
#include <sys/time.h>
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
