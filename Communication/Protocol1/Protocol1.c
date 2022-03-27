#include "Protocol1.h"

Ringbuffer_t ringbuffer;
Frame_t frame;

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

    if(frameIndex == 0)
    {
        if(byte != 0xDE)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == 1)
    {
        if(byte != 0xAD)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == 2)
    {
        if(byte != 0xBE)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == 3)
    {
        if(byte != 0xEF)
        {
            frameIndex = 0;
            return FrameBadPreamble;
        }
    }
    else if(frameIndex == 4)
    {
        frame.command = byte;
    }
    else if(frameIndex == 5)
    {
        frame.length = byte << 8;
    }
    else if(frameIndex == 6)
    {
        frame.length += byte;
        frame.data = (uint8_t*)malloc(frame.length);
    }
    else if(frameIndex >= 7 && frameIndex < 7 + frame.length)
    {
        frame.data[frameIndex - 7] = byte;
    }
    else if(frameIndex == 7 + frame.length)
    {
        frame.Crc16 = byte << 8;
    }
    else if(frameIndex == 7 + frame.length + 1)
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