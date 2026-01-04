#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ip.h"
#include <arpa/inet.h>
#include "datastructure/map.h"


static struct Map* l4LookupTable = NULL;

void printIpHeader(FILE *file, const IpHeader *header, const char* options);

void ip_registerL4Handler(IpType protocol, FilterHandler handler) {
    if (!l4LookupTable) {
        l4LookupTable = map_create();
    }
    map_put(l4LookupTable, &protocol, sizeof(IpType), handler);
}

void ip_init() {
    if (l4LookupTable) {
        map_destroy(l4LookupTable);
    }
    l4LookupTable = map_create();
}

void ip_cleanup() {
    if (l4LookupTable) {
        map_destroy(l4LookupTable);
        l4LookupTable = NULL;
    }
}

int ipHandler(FilterHandle* handle){
    if (handle->remaining < sizeof(IpHeader))
        return FLITER_HANDLER_NOT_ENOUGH_REMAINING;

    IpHeader iph;
    memcpy(&iph, handle->cursor, sizeof(IpHeader));
    int ihl = iph.verIhl & 0x0f;

    handle->cursor += sizeof(IpHeader);
    handle->remaining -= sizeof(IpHeader);


    size_t opt_len = (ihl - 5) * 4;
    char* options = NULL;
    if (opt_len > 0) {
        if (handle->remaining < opt_len)
            return FLITER_HANDLER_NOT_ENOUGH_REMAINING;

        options = malloc(opt_len);
        memcpy(options, handle->cursor, opt_len);
        handle->cursor   += opt_len;
        handle->remaining -= opt_len;
    }

    printIpHeader(stdout, &iph, options);
    if (options)
        free(options);

    IpType protocol = iph.protocol;
    if (l4LookupTable) {
        FilterHandler nextHandler = (FilterHandler)map_get(l4LookupTable, &protocol, sizeof(IpType));

        if (nextHandler) {
            return nextHandler(handle);
        }
    }

    return FILTER_HANDLER_SUCCESS;
}

void printIpHeader(FILE *file, const IpHeader *header, const char* options)
{
    if (!file || !header) return;

    unsigned char version = (header->verIhl >> 4) & 0x0F;
    unsigned char ihl     = header->verIhl & 0x0F;

    unsigned short totalLen = ntohs(header->length);
    unsigned short id       = ntohs(header->id);

    unsigned short frag = ntohs(header->flagsAndFragmentOffset);
    unsigned char  flags = (frag >> 13) & 0x07;
    unsigned int offset = frag & 0x1FFF;

    fprintf(file, "IP Header\n");
    fprintf(file, "  Version        : %u\n", version);
    fprintf(file, "  IHL            : %u (%u bytes)\n", ihl, ihl * 4);
    fprintf(file, "  TOS            : 0x%02X\n", header->tos);
    fprintf(file, "  Total Length   : %u\n", totalLen);
    fprintf(file, "  Identification : %u\n", id);
    fprintf(file, "  Flags          : 0x%X (DF=%d, MF=%d)\n",
            flags, !!(frag & 0x4000), !!(frag & 0x2000));
            // R (Reserved: 항상 0)
            // DF(Don't Fragment: Router에게 fragment하지말라고 지시)
            // MF(More Fragment: 이 뒤에 Fragment가 있는지 -> 마지막일 떄 0) 
    fprintf(file, "  Fragment Offset: %u (%u bytes)\n",
            offset, offset * 8); //offset은 8Byte 단위가 된다.
    fprintf(file, "  TTL            : %u\n", header->ttl);
    fprintf(file, "  Protocol       : %u\n", header->protocol);
    fprintf(file, "  Checksum       : 0x%04X\n",
            ntohs(header->checksum));

    fprintf(file, "  Source IP      : %u.%u.%u.%u\n",
            header->srcIp[0], header->srcIp[1],
            header->srcIp[2], header->srcIp[3]);

    fprintf(file, "  Destination IP : %u.%u.%u.%u\n",
            header->dstIp[0], header->dstIp[1],
            header->dstIp[2], header->dstIp[3]);

    if (options) {
        fprintf(file, "  options : %s \n", options);
    }
}