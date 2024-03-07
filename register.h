#ifndef __REGISTER_H__
#define __REGISTER_H__

class Register{
private:
    int value;
public:
    Register();    
    void setValue(int val);
    int getValue();
    void printValue();
};

#endif