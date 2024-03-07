#ifndef __WORD_H__
#define __WORD_H__

#include <string>
using std::string;

class Word{
public:
    string* data;
    Word();
    void initWord(char n);
    void copy(Word source);
    void print();
};

#endif