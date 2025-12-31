#include "filter.h"

#pragma pack(push,1)
typedef struct IpHeader{
    unsigned char verIhl; // Version(4bit) IHL(4bit)
    unsigned char tos;
    unsigned short length;
    unsigned short id;
    unsigned short flagsAndFragmentOffset;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short checksum;
    unsigned char srcIp[4];
    unsigned char dstIp[4];
}IpHeader;
#pragma pack(pop)

int ipHandler(FilterHandle* handle);