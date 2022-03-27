#include <gtest/gtest.h>
#include <stdlib.h>

static uint8_t* frameByteArray;
static uint16_t frameByteArrayLength;
static uint16_t readCounter;

extern "C"
{
    #include "../Protocol1.h"
    #include "../../Ringbuffer/RingbufferGeneric/RingbufferGeneric.h"

    bool RingbufferGetItem(Ringbuffer_t *buff, void *item)
    {
        if(frameByteArrayLength == readCounter)
            return false;

        memcpy(item, &frameByteArray[readCounter], sizeof(uint8_t));
        readCounter++;

        return true;
    }
}

struct ProtocolCreatingFramesTests : public ::testing::TestWithParam<std::tuple<FrameCommand_t, uint16_t, uint8_t*,  uint16_t>>
{
    Frame_t frame;
    uint8_t* data;
    FrameCommand_t command;
    uint16_t length;
    uint16_t crc;

    void SetUp() override 
    {
        command = std::get<0>(GetParam());
        length = std::get<1>(GetParam());
        data = (uint8_t*)malloc(length);
        memcpy(data, std::get<2>(GetParam()), length);
        crc = std::get<3>(GetParam());

        frameCreate(command, length, data, &frame);
    }

    void TearDown() override 
    {
        frameDelete(&frame);
        free(data);
    }
};

TEST_P(ProtocolCreatingFramesTests, FrameCreating)
{
    EXPECT_EQ(FRAME_PREAMBLE, frame.preamble);
    EXPECT_EQ(command, frame.command);
    EXPECT_EQ(length, frame.length);
    for(uint16_t i = 0; i < length; i++)
    {
        EXPECT_EQ(data[i], frame.data[i]);
    }
    EXPECT_EQ(crc, frame.Crc16);
}

uint8_t testData1[5] = {1, 2, 3 ,4 ,5};
uint8_t testData2[10] = {1, 2, 3 ,4 ,5, 6, 7, 8, 9, 10};

INSTANTIATE_TEST_SUITE_P(ProtocolCreatingFrames, ProtocolCreatingFramesTests, ::testing::Values(
    std::make_tuple(Cmd_GetMeasurement, 0, (uint8_t*)NULL, 0),
    std::make_tuple(Cmd_GetConfiguration, 0, (uint8_t*)NULL, 1),
    std::make_tuple(Cmd_SetConfiguration, 5, testData1, 22),
    std::make_tuple(Cmd_SetConfiguration, 10, testData2, 67)
));

struct ProtocolReceivingTests : public ::testing::TestWithParam<std::tuple<uint8_t*, uint16_t, char*>>
{
    char *expectedResult = std::get<2>(GetParam());

    void SetUp() override 
    {
        readCounter = 0;
        frameByteArrayLength = std::get<1>(GetParam());
        frameByteArray = (uint8_t*)malloc(frameByteArrayLength);
        memcpy(frameByteArray, std::get<0>(GetParam()), frameByteArrayLength);
    }

    void TearDown() override 
    {
        free(frameByteArray);
        frameByteArrayLength = 0;
    }
};

TEST_P(ProtocolReceivingTests, FrameProcessing)
{
    char* result = frameProcess();

    EXPECT_STREQ(expectedResult, result);
}

#define FRAME_SIZE_WITHOUT_DATA 9
char* testResultBadPreamble = "Bad preamble";
char* testResultBadCRC = "Bad CRC";
char* testResultGetMeasurementCommand = "Get measurement command";
char* testResultGetConfigurationCommand = "Get configuration command";
char* testResultSetConfigurationCommand = "Set configuration command";
char* testResultUnknownCommand = "Unknown command";

uint8_t testFrameBadPreamble1[FRAME_SIZE_WITHOUT_DATA] = {0xDE, 0xAF, 0xBE, 0xEF, Cmd_GetMeasurement, 0x00, 0x00, 0x00, 0x00};
uint8_t testFrameBadPreamble2[FRAME_SIZE_WITHOUT_DATA] = {0xDE, 0xAD, 0xBE, 0x1F, Cmd_GetConfiguration, 0x00, 0x00, 0x00, 0x01};
uint8_t testFrameUnknownCommand[FRAME_SIZE_WITHOUT_DATA] = {0xDE, 0xAD, 0xBE, 0xEF, 0x05, 0x00, 0x00, 0x00, 0x05};
uint8_t testFrameBadCRC1[FRAME_SIZE_WITHOUT_DATA + 2] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_GetMeasurement, 0x00, 0x02, 0x01, 0x01, 0x00, 0x05};
uint8_t testFrameBadCRC2[FRAME_SIZE_WITHOUT_DATA + 4] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_SetConfiguration, 0x00, 0x04, 0x01, 0x01, 0x05, 0x0A ,0x01, 0x50};
uint8_t testFrameMoreDataThenLength1[FRAME_SIZE_WITHOUT_DATA + 1] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_GetConfiguration, 0x00, 0x00, 0x25, 0x00, 0x01};
uint8_t testFrameMoreDataThenLength2[FRAME_SIZE_WITHOUT_DATA + 3] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_SetConfiguration, 0x00, 0x02, 0x01, 0x01, 0xAB, 0x00, 0x06};
uint8_t testFrameGetMeasurement1[FRAME_SIZE_WITHOUT_DATA] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_GetMeasurement, 0x00, 0x00, 0x00, 0x00};
uint8_t testFrameGetMeasurement2[FRAME_SIZE_WITHOUT_DATA + 2] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_GetMeasurement, 0x00, 0x02, 0xAB, 0xAD, 0x01, 0x5A};
uint8_t testFrameGetConfiguraton1[FRAME_SIZE_WITHOUT_DATA] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_GetConfiguration, 0x00, 0x00, 0x00, 0x01};
uint8_t testFrameSetConfiguraton1[FRAME_SIZE_WITHOUT_DATA + 30] = {0xDE, 0xAD, 0xBE, 0xEF, Cmd_SetConfiguration, 0x00, 0x1E,
                                                                   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                                                                   0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                                                                   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
                                                                   0x01, 0xD3};

INSTANTIATE_TEST_SUITE_P(ProtocolReceiveFrame, ProtocolReceivingTests, ::testing::Values(
    std::make_tuple(testFrameBadPreamble1, FRAME_SIZE_WITHOUT_DATA, testResultBadPreamble),
    std::make_tuple(testFrameBadPreamble2, FRAME_SIZE_WITHOUT_DATA, testResultBadPreamble),
    std::make_tuple(testFrameGetMeasurement1, FRAME_SIZE_WITHOUT_DATA, testResultGetMeasurementCommand),
    std::make_tuple(testFrameGetMeasurement2, FRAME_SIZE_WITHOUT_DATA + 2, testResultGetMeasurementCommand),
    std::make_tuple(testFrameGetConfiguraton1, FRAME_SIZE_WITHOUT_DATA, testResultGetConfigurationCommand),
    std::make_tuple(testFrameSetConfiguraton1, FRAME_SIZE_WITHOUT_DATA + 30, testResultSetConfigurationCommand),
    std::make_tuple(testFrameUnknownCommand, FRAME_SIZE_WITHOUT_DATA, testResultUnknownCommand),
    std::make_tuple(testFrameBadCRC1, FRAME_SIZE_WITHOUT_DATA + 2, testResultBadCRC),
    std::make_tuple(testFrameBadCRC2, FRAME_SIZE_WITHOUT_DATA + 4, testResultBadCRC),
    std::make_tuple(testFrameMoreDataThenLength1, FRAME_SIZE_WITHOUT_DATA + 1, testResultBadCRC),
    std::make_tuple(testFrameMoreDataThenLength2, FRAME_SIZE_WITHOUT_DATA + 3, testResultBadCRC)
));

