#include "gtest/gtest.h"
#include "M3LS.h"
using ::testing::Return;

TEST(Constructor, SingleAxis){
    // Initialize test parameters
    int pins[] = {1};
    int numAxes = 1;

    // Initialize mock Arduino and SPI
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SPIMock* spiMock = SPIMockInstance();

    // Set up expected calls for constructor
    EXPECT_CALL(*arduinoMock, delay(50));
    EXPECT_CALL(*spiMock, begin());
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }
    M3LS m3 = M3LS(pins[0]);

    // Set up expected calls for begin
    EXPECT_CALL(*arduinoMock, delay(250)).Times(4);
    m3.begin();

    // Cleanup mock
    releaseArduinoMock();
    releaseSPIMock();
}

TEST(Constructor, DoubleAxis){
    // Initialize test parameters
    int pins[] = {1, 2};
    int numAxes = 2;

    // Initialize mock Arduino and SPI
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SPIMock* spiMock = SPIMockInstance();

    // Set up expected calls for constructor
    EXPECT_CALL(*arduinoMock, delay(50));
    EXPECT_CALL(*spiMock, begin());
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }
    M3LS m3 = M3LS(pins[0], pins[1]);

    // Set up expected calls for begin
    EXPECT_CALL(*arduinoMock, delay(250)).Times(4);
    m3.begin();

    // Cleanup mock
    releaseArduinoMock();
    releaseSPIMock();
}

TEST(Constructor, TripleAxis){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
    int numAxes = 3;

    // Initialize mock Arduino and SPI
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SPIMock* spiMock = SPIMockInstance();

    // Set up expected calls for constructor
    EXPECT_CALL(*arduinoMock, delay(50));
    EXPECT_CALL(*spiMock, begin());
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);

    // Set up expected calls for begin
    EXPECT_CALL(*arduinoMock, delay(250)).Times(4);
    m3.begin();

    // Cleanup mock
    releaseArduinoMock();
    releaseSPIMock();
}

TEST(ToggleHold, SetHold){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
    int numAxes = 3;

    // Initialize mock Arduino and SPI
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SPIMock* spiMock = SPIMockInstance();

    // Set up expected calls for constructor
    EXPECT_CALL(*arduinoMock, delay(50));
    EXPECT_CALL(*spiMock, begin());
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);

    // Set up expected calls for begin
    EXPECT_CALL(*arduinoMock, delay(250)).Times(4);
    m3.begin();

    // Set up expected calls for setting the control mode
    m3.setControlMode(M3LS::hold);

    // Cleanup mock
    releaseArduinoMock();
    releaseSPIMock();
}

TEST(ToggleHold, SetPosition){
    // Initialize test parameters
    int pins[] = {1, 2, 3};
    int numAxes = 3;

    // Initialize mock Arduino and SPI
    ArduinoMock* arduinoMock = arduinoMockInstance();
    SPIMock* spiMock = SPIMockInstance();

    // Set up expected calls for constructor
    EXPECT_CALL(*arduinoMock, delay(50));
    EXPECT_CALL(*spiMock, begin());
    for (int pin = 0; pin < numAxes; pin++){
        EXPECT_CALL(*arduinoMock, pinMode(pins[pin], OUTPUT));
        EXPECT_CALL(*arduinoMock, digitalWrite(pins[pin], HIGH));
    }
    M3LS m3 = M3LS(pins[0], pins[1], pins[2]);

    // Set up expected calls for begin
    EXPECT_CALL(*arduinoMock, delay(250)).Times(4);
    m3.begin();

    // Set up expected calls for setting the control mode
    m3.setControlMode(M3LS::position);

    // Cleanup mock
    releaseArduinoMock();
    releaseSPIMock();
}