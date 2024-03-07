#include <cstdio>
#include <cstdlib>
#include "cpu.h"

CPU::CPU(int cache){
    cacheType=cache;
    nInst=0;

    OPCODE_RFORMAT="000000";
    OPCODE_ADDI="001000";
    OPCODE_ADDIU="001001";
    OPCODE_ANDI="001100";
    OPCODE_ORI="001101";
    OPCODE_LUI="001111";
    OPCODE_SLTI="001010";
    OPCODE_SLTIU="001011";
    OPCODE_BEQ="000100";
    OPCODE_BNE="000101";
    OPCODE_J="000010";
    OPCODE_JAL="000011";
    OPCODE_LW="100011";
    OPCODE_SW="101011";

    FUNCTYPE_ADD="100000";
    FUNCTYPE_ADDU="100001";
    FUNCTYPE_SUB="100010";
    FUNCTYPE_SUBU="100011";
    FUNCTYPE_AND="100100";
    FUNCTYPE_OR="100101";
    FUNCTYPE_SLT="101010";
    FUNCTYPE_SLTU="101011";
    FUNCTYPE_JR="001000";
    FUNCTYPE_SLL="000000";
    FUNCTYPE_SRL="000010";
    FUNCTYPE_SYSCALL="001100";
}

void CPU::load(Code code){
    inst.copy(code.getInst(pc.getValue()));
    pc.setValue(pc.getValue()+4);
}

bool CPU::compOPCode(string target){
    for(int i=0;i<6;i++){
        if(target[i]-'0'!=inst.data->at(i)){
            return false;
        }
    }

    return true;
}

bool CPU::compFuncType(string target){
    for(int i=0;i<6;i++){
        if(target[i]-'0'!=inst.data->at(i+26)){
            return false;
        }
    }

    return true;
}

int CPU::getRS(){
    int num=0;
    int digit=1;
    for(int i=10;i>=6;i--){
        if(inst.data->at(i)==1){
            num+=digit;
        }
        digit*=2;
    }
    return num;
}

int CPU::getRT(){
    int num=0;
    int digit=1;
    for(int i=15;i>=11;i--){
        if(inst.data->at(i)==1){
            num+=digit;
        }
        digit*=2;
    }
    return num;
}

int CPU::getRD(){
    int num=0;
    int digit=1;
    for(int i=20;i>=16;i--){
        if(inst.data->at(i)==1){
            num+=digit;
        }
        digit*=2;
    }
    return num;
}

int CPU::getSA(){
    int num=0;
    int digit=1;
    for(int i=25;i>=21;i--){
        if(inst.data->at(i)==1){
            num+=digit;
        }
        digit*=2;
    }
    return num;
}

int CPU::getImm(){
    int num=0;
    int digit=1;
    for(int i=31;i>=16;i--){
        if(inst.data->at(i)==1){
            num+=digit;
        }
        digit*=2;
    }
    return num;
}

int CPU::getTarget(){
    int num=0;
    int digit=1;
    for(int i=31;i>=6;i--){
        if(inst.data->at(i)==1){
            num+=digit;
        }
        digit*=2;
    }
    return num;
}

void CPU::accessMemory(DataMemory mem){
    memory=mem;
}

void CPU::accessCache(Cache1 cache){
    cache1=cache;
}

void CPU::accessCache(Cache2 cache){
    cache2=cache;
}

void CPU::printCacheHitMiss(){
    if(cacheType==1){
        cache1.printHitMiss();
    }else{
        cache2.printHitMiss();
    }
}

bool CPU::run(){
    nInst++;
    // printf("nInst: %d\n", ++nInst);
    if(compOPCode(OPCODE_RFORMAT)){
        if(compFuncType(FUNCTYPE_ADD)){
            ADD(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_ADDU)){
            ADDU(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_SUB)){
            SUB(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_SUBU)){
            SUBU(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_AND)){
            AND(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_OR)){
            OR(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_SLT)){
            SLT(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_SLTU)){
            SLTU(getRD(), getRS(), getRT());
        }else if(compFuncType(FUNCTYPE_JR)){
            JR(getRS());
        }else if(compFuncType(FUNCTYPE_SLL)){
            SLL(getRD(), getRT(), getSA());
        }else if(compFuncType(FUNCTYPE_SRL)){
            SRL(getRD(), getRT(), getSA());
        }else if(compFuncType(FUNCTYPE_SYSCALL)){
            SYSCALL();
        }else{
            UNKNOWN();
        }
    }else if(compOPCode(OPCODE_ADDI)){
        ADDI(getRT(), getRS(), getImm());
    }else if(compOPCode(OPCODE_ADDIU)){
        ADDIU(getRT(), getRS(), getImm());
    }else if(compOPCode(OPCODE_ANDI)){
        ANDI(getRT(), getRS(), getImm());
    }else if(compOPCode(OPCODE_ORI)){
        ORI(getRT(), getRS(), getImm());
    }else if(compOPCode(OPCODE_LUI)){
        LUI(getRT(), getImm());
    }else if(compOPCode(OPCODE_SLTI)){
        SLTI(getRT(), getRS(), getImm());
    }else if(compOPCode(OPCODE_SLTIU)){
        SLTIU(getRT(), getRS(), getImm());
    }else if(compOPCode(OPCODE_BEQ)){
        BEQ(getRS(), getRT(), getImm());
    }else if(compOPCode(OPCODE_BNE)){
        BNE(getRS(), getRT(), getImm());
    }else if(compOPCode(OPCODE_J)){
        J();
    }else if(compOPCode(OPCODE_JAL)){
        JAL();
    }else if(compOPCode(OPCODE_LW)){
        LW(getRS(), getRT(), getImm());
    }else if(compOPCode(OPCODE_SW)){
        SW(getRS(), getRT(), getImm());
    }else{
        UNKNOWN();
        return false;
    }
    return true;
}

void CPU::printInst(){
    printf("PC: 0x%.8x, inst: ", pc.getValue());
    inst.print();
    printf("\n");
}

void CPU::printRegisterValue(){
    for(int i=0;i<32;i++){
        printf("$%d: ", i);
        reg[i].printValue();
        printf("\n");
    }
    printf("PC: ");
    pc.printValue();
    printf("\n");
}

void CPU::printNInst(){
    printf("Instructions: %d\n", nInst);
}

void CPU::ADD(int rd, int rs, int rt){
    // printf("add $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue(reg[rs].getValue()+reg[rt].getValue());
}

void CPU::ADDU(int rd, int rs, int rt){
    // printf("addu $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue(reg[rs].getValue()+reg[rt].getValue());
}

void CPU::SUB(int rd, int rs, int rt){
    // printf("sub $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue(reg[rs].getValue()-reg[rt].getValue());
}

void CPU::SUBU(int rd, int rs, int rt){
    // printf("subu $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue(reg[rs].getValue()-reg[rt].getValue());
}

void CPU::AND(int rd, int rs, int rt){
    // printf("and $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue(reg[rs].getValue()&reg[rt].getValue());
}

void CPU::OR(int rd, int rs, int rt){
    // printf("or $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue(reg[rs].getValue()|reg[rt].getValue());
}

void CPU::SLT(int rd, int rs, int rt){
    // printf("slt $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue(reg[rs].getValue()<reg[rt].getValue()?1:0);
}

void CPU::SLTU(int rd, int rs, int rt){
    // printf("sltu $%d $%d $%d\n", rd, rs, rt);
    reg[rd].setValue((unsigned int)(reg[rs].getValue())<(unsigned int)(reg[rt].getValue())?1:0);
}

void CPU::JR(int rs){
    // printf("jr $%d\n", rs);
    pc.setValue(reg[rs].getValue());
}

void CPU::SLL(int rd, int rt, int sa){
    // printf("sll $%d $%d %d\n", rd, rt, sa);
    int rtValue=reg[rt].getValue();
    for(int i=0;i<sa;i++){
        rtValue*=2;
    }
    reg[rd].setValue(rtValue);
}

void CPU::SRL(int rd, int rt, int sa){
    // printf("srl $%d $%d %d\n", rd, rt, sa);
    unsigned int rtValue=reg[rt].getValue();
    for(int i=0;i<sa;i++){
        rtValue/=2;
    }
    reg[rd].setValue(rtValue);
}

void CPU::SYSCALL(){
    // printf("syscall\n");
    int v0Value=reg[2].getValue();
    // printf("value: %d\n", v0Value);
    if(v0Value==1){
        printf("%d", reg[4].getValue());
    }else if(v0Value==4){
        memory.readMemory(reg[4].getValue());
    }else if(v0Value==5){
        int input;
        scanf("%d", &input);
        reg[2].setValue(input);
    }
}

int CPU::signExtension(int n){
    if(n/32768==1){
        return n+SIGN_EXTENSION_OFFSET;
    }else{
        return n;
    }
}

void CPU::ADDI(int rt, int rs, int imm){
    // printf("addi $%d $%d %d(0x%x)\n", rt, rs, imm, imm);
    reg[rt].setValue(reg[rs].getValue()+signExtension(imm));
}

void CPU::ADDIU(int rt, int rs, int imm){
    // printf("addiu $%d $%d %d(0x%x)\n", rt, rs, imm, imm);
    reg[rt].setValue(reg[rs].getValue()+signExtension(imm));
}

void CPU::ANDI(int rt, int rs, int imm){
    // printf("andi $%d $%d %d(0x%x)\n", rt, rs, imm, imm);
    reg[rt].setValue(reg[rs].getValue()&imm);
}

void CPU::ORI(int rt, int rs, int imm){
    // printf("ori $%d $%d %d(0x%x)\n", rt, rs, imm, imm);
    reg[rt].setValue(reg[rs].getValue()|imm);
}

void CPU::LUI(int rt, int imm){
    // printf("lui $%d %d(0x%x)\n", rt, imm, imm);
    reg[rt].setValue(imm*65536);
}

void CPU::SLTI(int rt, int rs, int imm){
    // printf("slti $%d $%d %d(0x%x)\n", rt, rs, imm, imm);
    reg[rt].setValue(reg[rs].getValue()<signExtension(imm)?1:0);
}

void CPU::SLTIU(int rt, int rs, int imm){
    // printf("sltiu $%d $%d %d(0x%x)\n", rt, rs, imm, imm);
    reg[rt].setValue((unsigned int)reg[rs].getValue()<(unsigned int)signExtension(imm)?1:0);
}

void CPU::BEQ(int rt, int rs, int offset){
    // printf("beq $%d $%d %d(0x%x)\n", rt, rs, offset, offset);
    if(reg[rt].getValue()==reg[rs].getValue()){
        pc.setValue(pc.getValue()+signExtension(offset)*4);
    }
}

void CPU::BNE(int rt, int rs, int offset){
    // printf("bne $%d $%d %d(0x%x)\n", rt, rs, offset, offset);
    if(reg[rt].getValue()!=reg[rs].getValue()){
        pc.setValue(pc.getValue()+signExtension(offset)*4);
    }
}

void CPU::J(){
    // printf("j ");
    pc.setValue(getTarget()*4);
}

void CPU::JAL(){
    // printf("jal\n");
    reg[31].setValue(pc.getValue());
    pc.setValue(getTarget()*4);
}

void CPU::LW(int rs, int rt, int offset){
    // printf("lw $%d %d($%d)\n", rt, offset, rs);
    int address=reg[rs].getValue()+signExtension(offset);
    int value=memory.getMemory(address);
    reg[rt].setValue(value);
    if(cacheType==1){
        cache1.storeCache(address, true);
    }else{
        cache2.storeCache(address, true);
    }
}

void CPU::SW(int rs, int rt, int offset){
    // printf("sw $%d %d($%d)\n", rt, offset, rs);
    int address=reg[rs].getValue()+signExtension(offset);
    int value=reg[rt].getValue();
    memory.setMemory(address, value);
    if(cacheType==1){
        cache1.storeCache(address, false);
    }else{
        cache2.storeCache(address, true);
    }
}

void CPU::UNKNOWN(){
    // printf("unknown instruction\n");
    // printRegisterValue();
}