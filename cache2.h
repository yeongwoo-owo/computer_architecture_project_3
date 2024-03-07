#ifndef __CACHE2_H__
#define __CACHE2_H__

#define CACHE2_MAX_INDEX   16

typedef struct{
    int tag;        //22bit
    int index;      //4bit
    int offset;     //6bit
}cache2Address;

typedef struct{
    int nData;
    int valid[4];
    int tag[4];
}cache2Memory;

class Cache2{
private:
    cache2Memory memory[CACHE2_MAX_INDEX];

    int nHit;
    int nMiss;

public:
    Cache2();
    void storeCache(int addr, bool storePolicy);
    void printHitMiss();
};

#endif