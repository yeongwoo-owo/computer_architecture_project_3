#ifndef __CODE_H__
#define __CODE_H__

#define CODE_LEN  16384

#include "word.h"

class Code{
private:
    Word instMem[CODE_LEN];
    int nInst;

public:
    Code(int n);
    void setCode(unsigned char* buf, int n);
    Word getInst(int pc);
    // void printCode();
};

#endif