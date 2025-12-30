#include<stdio.h>
#include<stdlib.h>

size_t readNBytes(FILE* fp, char* buffer, size_t size){
    if (!fp || !buffer) return -1;
    
    size_t total = 0;
    unsigned char* p = buffer;

    while (total < size) {
        size_t n = fread(p + total, 1, size - total, fp);
        if (n == 0) {
            if (feof(fp)) break;
            if (ferror(fp)) return -1;
        }
        total += n;
    }
    return (size_t)total;

}