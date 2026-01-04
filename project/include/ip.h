#ifndef IP_H
#define IP_H

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

typedef enum {
    IpType_HOPOPTS = 0,   // IPv6 Hop-by-Hop (IPv6 전용)
    IpType_ICMP    = 1,   // ICMP
    IpType_IGMP    = 2,   // IGMP
    IpType_TCP     = 6,   // TCP
    IpType_UDP     = 17,  // UDP
    IpType_IPV6    = 41,  // IPv6 encapsulation
    IpType_ROUTING = 43,  // IPv6 routing header
    IpType_FRAGMENT= 44,  // IPv6 fragment header
    IpType_GRE     = 47,  // GRE
    IpType_ESP     = 50,  // IPsec ESP
    IpType_AH      = 51,  // IPsec AH
    IpType_ICMPV6  = 58,  // ICMPv6
    IpType_NONE    = 59,  // IPv6 no next header
    IpType_DSTOPTS = 60,  // IPv6 destination options
} IpType;

int ipHandler(FilterHandle* handle);

// 초기화 및 등록 함수
void ip_init();
void ip_cleanup();
void ip_registerL4Handler(IpType protocol, FilterHandler handler);

#endif