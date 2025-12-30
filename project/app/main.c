#include<stdio.h>
#include<stdlib.h>
#include "ioutil.h"

int main(){
    size_t size = 20;    
    while(1){
        char* buffer = malloc(sizeof(char) * size);
        int ret = readNBytes(stdin, buffer, size);  
        
        if(ret == -1){
            puts("something error!!");
        }

        if(ret == 0){
            puts("EOF Occurred");
            break;
        }
        puts(buffer);
        free(buffer);
    }  
}