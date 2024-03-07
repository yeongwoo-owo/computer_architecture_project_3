#include <iostream>
#include <fstream>
#include <cstdlib>
#include "code.h"
#include "cpu.h"
#include "cache1.h"
#include "cache2.h"

#define MAX_BUF 10000

using std::cout;
using std::endl;

bool isDataFileExist(int argc){
    if(argc==5){
        return true;
    }else{
        return false;
    }
}

int getBinaryInput(FILE* input, unsigned char* buf){
    fseek(input, 0, SEEK_END);
    int pos=ftell(input);
    fseek(input, 0, SEEK_SET);
    fread(buf, pos, 1, input);
    return pos;
}

int main(int argc, char** argv){
    int cacheType=atoi(argv[1]);
    int nInst=atoi(argv[2]);
    FILE* instFile=fopen(argv[3], "rb");
    FILE* dataFile;
    if(isDataFileExist(argc)){
        dataFile=fopen(argv[4], "rb");
    }
    
    unsigned char buf[MAX_BUF];
    int nInput=getBinaryInput(instFile, buf)/4;


    Code code(nInst);
    code.setCode(buf, nInput);
    // code.printCode();

    DataMemory memory;
    memory.init();
    if(isDataFileExist(argc)){
        int nData=getBinaryInput(dataFile, buf);
        // printf("nData: %d\n", nData);
        memory.setData(nData, buf);
        // memory.printMemory();
        // printf("\n");
    }

    CPU cpu(cacheType);
    Cache1 cache1;
    Cache2 cache2;
    if(cacheType==1){
        cpu.accessCache(cache1);
    }else{
        cpu.accessCache(cache2);
    }
    
    cpu.accessMemory(memory);

    for(int i=0;i<nInst;i++){
        cpu.load(code);
        // cpu.printInst();
        if(!cpu.run()){
            break;
        }
        // cpu.printRegisterValue();
    }

    // printf("\n\nresult\n");
    // cpu.printRegisterValue();

    // if(isDataFileExist(argc)){
    //     memory.printMemory();
    //     printf("\n");
    // }

    cpu.printNInst();
    cpu.printCacheHitMiss();

    fclose(instFile);
    if(isDataFileExist(argc)){
        fclose(dataFile);
    }

    return 0;
}
