#ifndef PROTOCOL1_H
#define PROTOCOL1_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../../Ringbuffer/RingbufferGeneric/RingbufferGeneric.h"

#define FRAME_PREAMBLE 0xDEADBEEF
#define PREAMBLE_BYTE_1 ((uint8_t)(FRAME_PREAMBLE >> 24))
#define PREAMBLE_BYTE_2 ((uint8_t)(FRAME_PREAMBLE >> 16))
#define PREAMBLE_BYTE_3 ((uint8_t)(FRAME_PREAMBLE >> 8))
#define PREAMBLE_BYTE_4 ((uint8_t)FRAME_PREAMBLE)

typedef enum
{
    Cmd_GetMeasurement,
    Cmd_GetConfiguration,
    Cmd_SetConfiguration,
}FrameCommand_t;

typedef enum
{
    FrameOk,
    FrameInProgress,
    FrameBadPreamble,
    FrameBadCrc16,
}FrameResult_t;

typedef struct
{
    uint32_t preamble;
    FrameCommand_t command;
    uint16_t length;
    uint8_t* data;
    uint16_t Crc16;
}Frame_t;

void frameCreate(FrameCommand_t cmd, uint16_t len, uint8_t *data, Frame_t *frame);
void frameDelete(Frame_t *frame);
char* frameProcess(void);

#endif /* PROTOCOL1_H */