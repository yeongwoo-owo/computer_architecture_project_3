#ifndef __CACHE1_H__
#define __CACHE1_H__

#define CACHE1_MAX_INDEX   32

typedef struct{
    int tag;        //24bit
    int index;      //5bit
    int offset;     //5bit(8)
}cache1Address;

typedef struct{
    int valid;
    int tag;
}cache1Memory;

class Cache1{
private:
    cache1Memory memory[CACHE1_MAX_INDEX];

    int nHit;
    int nMiss;

public:
    Cache1();
    void storeCache(int addr, bool storePolicy);
    void printHitMiss();
};

#endif