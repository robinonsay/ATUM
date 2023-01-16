#ifndef MAAT_MSGS_H
#define MAAT_MSGS_H

#define LOG_SIZE        (128)
#define DATA_RAW_SIZE  (64)
#define NUM_TELEM_ITEMS (8)

typedef enum MAAT_DATA_TYPE_TAG
{
    TELEM_FLOAT= 0,
    TELEM_DOUBLE= 1,
    TELEM_INT= 2,
    TELEM_UINT= 3,
    TELEM_LONG= 4,
    TELEM_ULONG= 5,
    TELEM_LLONG= 6,
    TELEM_ULLONG= 7,
    TELEM_RAW=8,
    TELEM_NONE=9
} MAAT_DATA_TYPE_T;

typedef enum MAAT_MSG_TYPE_TAG
{
    MSG_TELEM = 0,
    MSG_LOG = 1,
    MSG_CMD = 2
} MAAT_MSG_TYPE_T;

typedef union MAAT_DATA_TAG
{
    float               fFloat;
    double              dDouble;
    int                 iInt;
    unsigned int        uiInt;
    long                lLong;
    unsigned long       ulLong;
    long long           llLongLong;
    unsigned long long  ullLongLong;
    char                raw[DATA_RAW_SIZE];
} MAAT_DATA_T;

typedef struct MAAT_MSG_HDR_TAG
{
    unsigned long       ulMid;
    unsigned long       ulSize;
    MAAT_MSG_TYPE_T     type;
} MAAT_MSG_HDR_T;

typedef struct MAAT_TELEM_TAG
{
    MAAT_DATA_TYPE_T    type;
    MAAT_DATA_T         data;
} MAAT_TELEM_T;

typedef struct MAAT_CMD_TAG
{
    uint8_t             uiCmdId;
    MAAT_DATA_TYPE_T    type;
    MAAT_DATA_T         data;
} MAAT_CMD_T;

typedef struct MAAT_MSG_TAG
{
    MAAT_MSG_HDR_T    hdr;
    union
    {
        MAAT_CMD_T      cmd;
        MAAT_TELEM_T    telem;
        char            log[LOG_SIZE];
    } data;
    uint16_t            crc;
} MAAT_MSG_T;

#endif /* MAAT_MSGS_H */
