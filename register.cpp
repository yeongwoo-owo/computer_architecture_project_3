#include <cstdio>
#include "register.h"

Register::Register(){
    value=0;
}

void Register::setValue(int val){
    value=val;
}

int Register::getValue(){
    return value;
}

void Register::printValue(){
    printf("0x%.8x", value);
}