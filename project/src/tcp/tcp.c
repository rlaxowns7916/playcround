#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "filter.h"
#include "tcp.h"

const int TCP_HEADER_SIZE = 20;

void printTcpHeader(FILE* file, const TcpHeader *header, const char* options, char* data);

int tcpHandler(FilterHandle* handle){
    if (handle->remaining < sizeof(TcpHeader))
        return FLITER_HANDLER_NOT_ENOUGH_REMAINING;

    TcpHeader tcph;
    memcpy(&tcph, handle->cursor, sizeof(TcpHeader));
    int headerLength = (ntohs(tcph.optFlags) & 0xF000) >> 12;

    handle->cursor += sizeof(TcpHeader);
    handle->remaining -= sizeof(TcpHeader);

    int optionSize = (4 * headerLength) - TCP_HEADER_SIZE;
    if(handle->remaining < optionSize){
        return FLITER_HANDLER_NOT_ENOUGH_REMAINING;
    }

    char* options = malloc(optionSize);
    memcpy(options, handle->cursor, optionSize);

    handle->cursor += optionSize;
    handle->remaining -= optionSize;

    printTcpHeader(stdout, &tcph, options, handle->cursor);

    if(options){
        free(options);
    }

    return FILTER_HANDLER_SUCCESS;
}

void printTcpHeader(FILE *file, const TcpHeader *header, const char* options, char* data){
    
    char headerLength = (ntohs(header->optFlags) & 0xF000) >> 12;
    char urg = (ntohs(header->optFlags) & 0x0020) >> 5;
    char ack = (ntohs(header->optFlags) & 0x0010) >> 4;
    char psh = (ntohs(header->optFlags) & 0x0008) >> 3;
    char rst = (ntohs(header->optFlags) & 0x0004) >> 2;
    char syn =(ntohs(header->optFlags) & 0x0002) >> 1;
    char fin = (ntohs(header->optFlags) & 0x0001);
    
    
    
    fprintf(file, "TCP Header\n");
    fprintf(file, "  srcPort        : %u\n", ntohs(header->srcPort));
    fprintf(file, "  dstPort            : %u\n", ntohs(header->dstPort));
    fprintf(file, "  seq            : %u\n", ntohs(header->sequence));
    fprintf(file, "  ack            : %u\n", ntohs(header->ack));
    fprintf(file, "  headerLength            : %u\n", headerLength);
    fprintf(file, "  urg            : %u\n", urg);
    fprintf(file, "  ack            : %u\n", ack);
    fprintf(file, "  psh            : %u\n", psh);
    fprintf(file, "  rst            : %u\n", rst);
    fprintf(file, "  fin            : %u\n", fin);
    fprintf(file, "  windowSize            : %u\n", ntohs(header->windowSize));
    fprintf(file, "  checkSum            : %u\n", ntohs(header->checkSum));
    fprintf(file, "  urgent            : %u\n", ntohs(header->urgent));
    fprintf(file, "  options            : %s\n", options);
    fprintf(file, "  data               : %s\n", data);
}