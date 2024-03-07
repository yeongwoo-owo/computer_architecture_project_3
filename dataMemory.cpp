#include "dataMemory.h"

void DataMemory::init(){
    memory=new string(MEM_LEN, -1);
}

void DataMemory::setData(int n, unsigned char* buf){
    nData=n;

    for(int i=0;i<nData;i++){
        (*memory)[i]=buf[i];
    }
}

void DataMemory::setMemory(unsigned int addr, unsigned int n){
    addr-=DATA_MEMORY_OFFSET;
    for(int i=3;i>=0;i--){
        (*memory)[addr+i]=n%256;
        n/=256;
    }
}

int DataMemory::getMemory(unsigned int addr){
    int n=0;
    addr-=DATA_MEMORY_OFFSET;
    for(int i=0;i<4;i++){
        n*=256;
        n+=(unsigned char)(*memory)[addr+i];
    }

    return n;
}

void DataMemory::readMemory(unsigned int addr){
    addr-=DATA_MEMORY_OFFSET;
    while(true){
        char c=(*memory)[addr];
        if(c==0||c==-1){
            break;
        }

        printf("%c", c);
        addr++;
    }
}

void DataMemory::printMemory(){
    for(int i=0;i<nData;i++){
        printf("memory %d: 0x%.2x(%d)\n", i, (unsigned char)(*memory)[i], (unsigned char)(*memory)[i]);
    }
}