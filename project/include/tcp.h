#include "filter.h"

#ifndef TCP_H
#define TCP_H

#pragma pack(push, 1)
typedef struct TcpHeader{
    unsigned short srcPort;
    unsigned short dstPort;
    unsigned int sequence;
    unsigned int ack;
    unsigned short optFlags;
    unsigned short windowSize;
    unsigned short checkSum;
    unsigned short urgent;
}TcpHeader;
#pragma pack(pop)

int tcpHandler(FilterHandle* handle);

#endif