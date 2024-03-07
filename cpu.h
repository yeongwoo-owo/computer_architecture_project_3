#ifndef __CPU_H__
#define __CPU_H__

#define N_REGISTER   32
#define SIGN_EXTENSION_OFFSET   4294901760

#include <string>
#include "word.h"
#include "register.h"
#include "code.h"
#include "dataMemory.h"
#include "cache1.h"
#include "cache2.h"

using std::string;

class CPU{
private:
    int cacheType;
    int nInst;
    Cache1 cache1;
    Cache2 cache2;
    Word inst;
    Register reg[N_REGISTER];
    Register pc;
    DataMemory memory;

    string OPCODE_RFORMAT;
    string OPCODE_ADDI;
    string OPCODE_ADDIU;
    string OPCODE_ANDI;
    string OPCODE_ORI;
    string OPCODE_LUI;
    string OPCODE_SLTI;
    string OPCODE_SLTIU;
    string OPCODE_BEQ;
    string OPCODE_BNE;
    string OPCODE_J;
    string OPCODE_JAL;
    string OPCODE_LW;
    string OPCODE_SW;

    string FUNCTYPE_ADD;
    string FUNCTYPE_ADDU;
    string FUNCTYPE_SUB;
    string FUNCTYPE_SUBU;
    string FUNCTYPE_AND;
    string FUNCTYPE_OR;
    string FUNCTYPE_SLT;
    string FUNCTYPE_SLTU;
    string FUNCTYPE_JR;
    string FUNCTYPE_SLL;
    string FUNCTYPE_SRL;
    string FUNCTYPE_SYSCALL;
public:
    CPU(int cache);
    void load(Code code);
    bool compOPCode(string target);
    bool compFuncType(string target);

    int getRS();
    int getRT();
    int getRD();
    int getSA();
    int getImm();
    int getTarget();

    void accessMemory(DataMemory mem);
    void accessCache(Cache1 cache);
    void accessCache(Cache2 cache);

    bool run();
    void printInst();
    void printRegisterValue();
    void printNInst();
    void printCacheHitMiss();

    int signExtension(int n);

    void intToWord(int n, Word w);
    int wordToInt(Word w);

    void ADD(int rd, int rs, int rt);
    void ADDU(int rd, int rs, int rt);
    void SUB(int rd, int rs, int rt);
    void SUBU(int rd, int rs, int rt);
    void AND(int rd, int rs, int rt);
    void OR(int rd, int rs, int rt);
    void SLT(int rd, int rs, int rt);
    void SLTU(int rd, int rs, int rt);
    void JR(int rs);
    void SLL(int rd, int rt, int sa);
    void SRL(int rd, int rt, int sa);
    void SYSCALL();
    void ADDI(int rt, int rs, int imm);
    void ADDIU(int rt, int rs, int imm);
    void ANDI(int rt, int rs, int imm);
    void ORI(int rt, int rs, int imm);
    void LUI(int rt, int imm);
    void SLTI(int rt, int rs, int imm);
    void SLTIU(int rt, int rs, int imm);
    void BEQ(int rs, int rt, int offset);
    void BNE(int rs, int rt, int offset);
    void J();
    void JAL();
    void LW(int rs, int rt, int offset);
    void SW(int rs, int rt, int offset);
    void UNKNOWN();
};

#endif