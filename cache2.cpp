#include "cache2.h"
#include <cstdio>

Cache2::Cache2(){
    nHit=0;
    nMiss=0;

    for(int i=0;i<CACHE2_MAX_INDEX;i++){
        memory[i].nData=0;
        for(int j=0;j<4;j++){
            memory[i].valid[j]=0;
        }
    }
}

void Cache2::storeCache(int addr, bool storePolicy){
    cache2Address address;

    address.offset=addr%64;
    addr/=64;
    address.index=addr%16;
    addr/=16;
    address.tag=addr;

    // printf("offset: %d, index: %d, tag: 0x%x\n", address.offset, address.index, address.tag);

    int setIdx;
    for(setIdx=0;setIdx<4;setIdx++){
        if(memory[address.index].valid[setIdx]==0){                //miss codnition 1
            nMiss++;
            // printf("Miss!: %d\n", nMiss);

            if(storePolicy){
                (memory[address.index].nData)++;
                memory[address.index].valid[setIdx]=1;
                memory[address.index].tag[setIdx]=address.tag;
            }
            // printf("\n");
            return;
        }

        if(memory[address.index].tag[setIdx]==address.tag){              //hit condition
            nHit++;
            // printf("Hit!: %d\n", nHit);

            for(int i=setIdx+1;i<(memory[address.index].nData);i++){
                memory[address.index].tag[i-1]=memory[address.index].tag[i];
            }
            memory[address.index].tag[(memory[address.index].nData)-1]=address.tag;
            return;
        }
    }

    //miss condition 2
    nMiss++;
    // printf("Miss!: %d\n", nMiss);

    if(storePolicy){
        for(int i=1;i<(memory[address.index].nData);i++){
            memory[address.index].tag[i-1]=memory[address.index].tag[i];
        }
        memory[address.index].tag[(memory[address.index].nData)-1]=address.tag;
    }
    // printf("\n");
    return;
}

void Cache2::printHitMiss(){
    printf("Total: %d\nHit: %d\nMiss: %d\n", nHit+nMiss, nHit, nMiss);
}