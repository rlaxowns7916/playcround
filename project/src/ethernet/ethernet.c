#include<stdio.h>
#include<stdlib.h>
#include "ethernet.h"
#include <arpa/inet.h>
#include "filter.h"

char* typeToString(unsigned short type);

int ethernetHandler(FilterHandle* handle){
    if (handle->remaining < sizeof(EthernetHeader))
        return FLITER_HANDLER_NOT_ENOUGH_REMAINING;
    
    EthernetHeader eth;
    memcpy(&eth, handle->cursor, sizeof(EthernetHeader));

    printEthernetHeader(stdout, &eth);
    handle->cursor += sizeof(EthernetHeader);
    handle->remaining -= sizeof(EthernetHeader);
    

    return FILTER_HANDLER_SUCCESS;
}

void printEthernetHeader(FILE *file, EthernetHeader *header)
{
    if (!file || !header) {
        return;
    }

    fprintf(file, "Ethernet Header\n");
    fprintf(file, "  Destination MAC : %02X:%02X:%02X:%02X:%02X:%02X\n",
            header->dstMac[0], header->dstMac[1], header->dstMac[2],
            header->dstMac[3], header->dstMac[4], header->dstMac[5]);

    fprintf(file, "  Source MAC      : %02X:%02X:%02X:%02X:%02X:%02X\n",
            header->srcMac[0], header->srcMac[1], header->srcMac[2],
            header->srcMac[3], header->srcMac[4], header->srcMac[5]);

    char* type = typeToString(ntohs(header->type));
    fprintf(file, "  EtherType       : %s\n", type);
}

char* typeToString(unsigned short type)
{
    switch (type) {
    case 0x0800: return "IPv4";
    case 0x0806: return "ARP";
    case 0x86DD: return "IPv6";
    case 0x8100: return "VLAN";
    default:     return "Unknown";
    }
}