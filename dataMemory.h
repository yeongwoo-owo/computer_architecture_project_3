#ifndef __DATA_MEMORY_H__
#define __DATA_MEMORY_H__

#define DATA_MEMORY_OFFSET  268435456
#define MEM_LEN             65536

#include "word.h"

class DataMemory{
private:
    string* memory;
    int nData;
    
public:
    void init();
    void setData(int n, unsigned char* buf);
    void setMemory(unsigned int addr, unsigned int n);
    int getMemory(unsigned int addr);
    void readMemory(unsigned int addr);

    void printMemory();
};

#endif