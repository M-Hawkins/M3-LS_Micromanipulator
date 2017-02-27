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
