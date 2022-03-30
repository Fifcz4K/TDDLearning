#include "Protocol1.h"

Ringbuffer_t ringbuffer;
Frame_t frame;

#define FRAME_INDEX_PREAMBLE_BYTE_1 0
#define FRAME_INDEX_PREAMBLE_BYTE_2 1
#define FRAME_INDEX_PREAMBLE_BYTE_3 2
#define FRAME_INDEX_PREAMBLE_BYTE_4 3
#define FRAME_INDEX_COMMAND 4
#define FRAME_INDEX_LENGTH_BYTE_1 5
#define FRAME_INDEX_LENGTH_BYTE_2 6
#define FRAME_INDEX_DATA_BYTE_1 7
#define FRAME_INDEX_CRC_BYTE_1(DATA_LEN) FRAME_INDEX_DATA_BYTE_1 + DATA_LEN
#define FRAME_INDEX_CRC_BYTE_2(DATA_LEN) FRAME_INDEX_DATA_BYTE_1 + DATA_LEN + 1

static uint16_t frameCountCRC16(Frame_t *frame)
{
    uint16_t crc = 0;

    crc = crc + frame->command;
    crc = crc + frame->length;
    for(uint16_t i = 0; i < frame->length; i++)
    {
        crc = crc + frame->data[i];
    }

    return crc;
}

void frameCreate(FrameCommand_t cmd, uint16_t len, uint8_t *data, Frame_t *frame)
{
    frame->preamble = FRAME_PREAMBLE;
    frame->command = cmd;
    frame->length = len;
    frame->data = (uint8_t*)malloc(len);
    memcpy(frame->data, data, len);
    frame->Crc16 = frameCountCRC16(frame);
}

void frameDelete(Frame_t *frame)
{
    free(frame->data);
}

static FrameResult_t frameProcessByte(uint8_t byte)
{
    static uint16_t frameIndex;

    if(frameIndex == FRAME_INDEX_PREAMBLE_BYTE_1)
    {
        if(byte != PREAMBLE_BYTE_1)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == FRAME_INDEX_PREAMBLE_BYTE_2)
    {
        if(byte != PREAMBLE_BYTE_2)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == FRAME_INDEX_PREAMBLE_BYTE_3)
    {
        if(byte != PREAMBLE_BYTE_3)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == FRAME_INDEX_PREAMBLE_BYTE_4)
    {
        if(byte != PREAMBLE_BYTE_4)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == FRAME_INDEX_COMMAND)
    {
        frame.command = byte;
    }
    else if(frameIndex == FRAME_INDEX_LENGTH_BYTE_1)
    {
        frame.length = byte << 8;
    }
    else if(frameIndex == FRAME_INDEX_LENGTH_BYTE_2)
    {
        frame.length += byte;
        frame.data = (uint8_t*)malloc(frame.length);
    }
    else if(frameIndex >= FRAME_INDEX_DATA_BYTE_1 && frameIndex < FRAME_INDEX_CRC_BYTE_1(frame.length))
    {
        frame.data[frameIndex - FRAME_INDEX_DATA_BYTE_1] = byte;
    }
    else if(frameIndex == FRAME_INDEX_CRC_BYTE_1(frame.length))
    {
        frame.Crc16 = byte << 8;
    }
    else if(frameIndex == FRAME_INDEX_CRC_BYTE_2(frame.length))
    {
        frame.Crc16 += byte;
        uint16_t crc = frameCountCRC16(&frame);
        frameIndex = 0;

        if(crc != frame.Crc16)
        {
            free(frame.data);
            return FrameBadCrc16;
        }

        return FrameOk;
    }

    frameIndex++;

    return FrameInProgress;
}

static char* processCommand(Frame_t *frame)
{
    switch(frame->command)
    {
        case Cmd_GetMeasurement:
            return "Get measurement command";
        
        case Cmd_GetConfiguration:
            return "Get configuration command";

        case Cmd_SetConfiguration:  
            return "Set configuration command";

        default:
            return "Unknown command";
    }
}

char* frameProcess(void)
{
    uint8_t item = 0;
    FrameResult_t res;
    char* retVal = NULL;
    while(RingbufferGetItem(&ringbuffer, &item))
    {
        res = frameProcessByte(item);

        switch(res)
        {
            case FrameOk:
                retVal = processCommand(&frame);
                free(frame.data);
                return retVal;

            case FrameInProgress:
            break;

            case FrameBadPreamble:
                return "Bad preamble";

            case FrameBadCrc16:
                return "Bad CRC";

            default:
                break;
        }
    }

    return NULL;
}