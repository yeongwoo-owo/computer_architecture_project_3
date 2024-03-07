#include <cstdio>
#include "word.h"

#define WORDLEN 32

Word::Word(){
    data=new string(WORDLEN, 1);
}

void Word::initWord(char n){
    for(int i=0;i<WORDLEN;i++){
        data->at(i)=n;
    }
}

void Word::copy(Word source){
    data=source.data;
}

void Word::print(){
    for(int i=0;i<WORDLEN;i++){
        printf("%d", (*data)[i]);
        if(i%4==3){
            printf(" ");
        }
    }
}