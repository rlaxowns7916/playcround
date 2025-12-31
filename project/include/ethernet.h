#include<string.h>
#include "filter.h"

#pragma pack(push,1)
typedef struct EthernetHeader{
    unsigned char dstMac[6];
    unsigned char srcMac[6];
    unsigned short type; // network byte order (BigEndian)
}EthernetHeader;
#pragma pack(pop)

typedef enum {
    ETHERTYPE_IPV4 = 0x0800,
    ETHERTYPE_ARP  = 0x0806,
    ETHERTYPE_IPV6 = 0x86DD,
} EtherType;


int ethernetHandler(FilterHandle* handle);