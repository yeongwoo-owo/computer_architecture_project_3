#include <cstdio>
#include "code.h"

Code::Code(int n){
    for(int i=0;i<CODE_LEN;i++){
        instMem[i].initWord(1);
    }
    nInst=n;
}

void Code::setCode(unsigned char* buf, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            int byte=int(buf[4*i+j]);

            int digit=8;
            while(digit!=0){
                instMem[i].data->at(j*8+(--digit))=byte%2;
                byte/=2;
            }
        }
    }
}

Word Code::getInst(int pc){
    return instMem[pc/4];
}

// void Code::printCode(){
//     for(int i=0;i<nInst;i++){
//         printf("inst %d: ", i);
//         instMem[i].print();
//         printf("\n");
//     }
// }