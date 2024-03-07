#include "cache1.h"
#include <cstdio>

Cache1::Cache1(){
    nHit=0;
    nMiss=0;

    for(int i=0;i<CACHE1_MAX_INDEX;i++){
        memory[i].valid=0;
    }
}

void Cache1::storeCache(int addr, bool storePolicy){
    cache1Address address;

    address.offset=addr%32;
    addr/=32;
    address.index=addr%32;
    addr/=32;
    address.tag=addr;

    // printf("offset: %d, index: %d, tag: 0x%x\n", address.offset, address.index, address.tag);
    
    if(memory[address.index].valid==1&&memory[address.index].tag==address.tag){
        nHit++;
        // printf("Hit!: %d\n\n", nHit);
    }else{
        nMiss++;
        // printf("Miss!: %d\n\n", nMiss);
        if(storePolicy){
            memory[address.index].valid=1;
            memory[address.index].tag=address.tag;
        }
    }
}

void Cache1::printHitMiss(){
    printf("Total: %d\nHit: %d\nMiss: %d\n", nHit+nMiss, nHit, nMiss);
}