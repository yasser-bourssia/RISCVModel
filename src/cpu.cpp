#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
#include "../includes/cpu.h"


using namespace std;

// Helping functions to help decode the OP (Shifting and ANDing to get the correct bits)
  
// What each bit represents can be found in RISC-V's official ISA.


//--------------------------------------------------------------------------------------------

int opcode_f(uint32_t inst){
    return inst & 0x7f;
}

int funct3_f(uint32_t inst){
    return (inst >> 12) & 0x7;
}
int funct7_f(uint32_t inst){
    return (inst >> 25) & 0x7f; 
}

uint64_t rd(uint32_t inst) {
    return (inst >> 7) & 0x1f;    // rd in bits 11..7
}
uint64_t rs1(uint32_t inst) {
    return (inst >> 15) & 0x1f;   // rs1 in bits 19..15
}
uint64_t rs2(uint32_t inst) {
    return (inst >> 20) & 0x1f;   // rs2 in bits 24..20
}
uint64_t imm_I(uint32_t inst) {
    // imm[11:0] = inst[31:20]
    return ((int64_t)(int32_t) (inst & 0xfff00000)) >> 20;
}
uint64_t imm_S(uint32_t inst) {
    // imm[11:5] = inst[31:25], imm[4:0] = inst[11:7]
    return ((int64_t)(int32_t)(inst & 0xfe000000) >> 20)
        | ((inst >> 7) & 0x1f);
}
uint64_t imm_B(uint32_t inst) {
    // imm[12|10:5|4:1|11] = inst[31|30:25|11:8|7]
    return ((int64_t)(int32_t)(inst & 0x80000000) >> 19)
        | ((inst & 0x80) << 4) // imm[11]
        | ((inst >> 20) & 0x7e0) // imm[10:5]
        | ((inst >> 7) & 0x1e); // imm[4:1]
}
uint64_t imm_U(uint32_t inst) {
    // imm[31:12] = inst[31:12]
    return (int64_t)(int32_t)(inst & 0xfffff999);
}
uint64_t imm_J(uint32_t inst) {
    // imm[20|10:1|11|19:12] = inst[31|30:21|20|19:12]
    return (uint64_t)((int64_t)(int32_t)(inst & 0x80000000) >> 11)
        | (inst & 0xff000) // imm[19:12]
        | ((inst >> 9) & 0x800) // imm[11]
        | ((inst >> 20) & 0x7fe); // imm[10:1]
}
uint32_t shamt(uint32_t inst) {
    // shamt(shift amount) only required for immediate shift instructions
    // shamt[4:5] = imm[5:0]
    return (uint32_t) (imm_I(inst) & 0x1f); // TODO: 0x1f / 0x3f ?
}


//--------------------------------------------------------------------------------------------

// What does the CPU class constructor do?
CPU::CPU(){

    cout << "CPU Class called \n";

}
// Increment Program Counter function after taking an instruction from DRAM
void CPU::incrementPC(){


    pc_reg++;

}
// Set CPU regs to 0.
void CPU::ResetCPU(){


    memset(reg, 0, sizeof(uint64_t)*32);
    reg[2] = DRAM_BASE + DRAM_SIZE;
    pc_reg = DRAM_BASE;

}



uint32_t CPU::cpu_fetch(){

    uint32_t inst = bus.bus_load(pc_reg, 32);

    return inst;

}


uint64_t CPU::cpu_load(uint64_t addr, uint64_t size){

    return bus.bus_load(addr, size);


}

uint64_t CPU::cpu_store(uint64_t addr, uint64_t size, uint64_t value){

    bus.bus_store(addr, size, value);


}


int CPU::cpu_execute(uint32_t inst){

    int opcode = opcode_f(inst);           // opcode in bits 6..0
    int funct3 = funct3_f(inst);    // funct3 in bits 14..12
    int funct7 = funct7_f(inst);   // funct7 in bits 31..25

    reg[0] = 0;                   // x0 hardwired to 0 at each cycle


    switch (opcode) {
    case I_TYPE:
        switch (funct3) {
            case ADDI:  exec_ADDI(inst); break;
            case SLLI:  exec_SLLI(inst); break;
            case SLTI:  exec_SLTI(inst); break;
            case SLTIU: exec_SLTIU(inst); break;
            case XORI:  exec_XORI(inst); break;
            case SRI:
                switch (funct7) {
                    case SRLI:  exec_SRLI(inst); break;
                    case SRAI:  exec_SRAI(inst); break;
                    default: ;
                } break;
            case ORI:   exec_ORI(inst); break;
            case ANDI:  exec_ANDI(inst); break;
            default: ;
        } break;

    default:
        fprintf(stderr,
                "[-] ERROR-> opcode:0x%x, funct3:0x%x, funct3:0x%x\n"
                , opcode, funct3, funct7);
        return 0;
        /*exit(1);*/
                }


}


// ---------------- Instruction exec functions -------------------------------

// I-type instructions -----

void CPU::exec_ADDI(uint32_t inst){

    reg[rd(inst)] = reg[rs1(inst)] + (int64_t) imm_I(inst);

}

void CPU::exec_SLLI(uint32_t inst){

    reg[rd(inst)] = (uint64_t) reg[rs1(inst)] << shamt(inst) ;

}

void CPU::exec_SLTI(uint32_t inst){

    reg[rd(inst)] = ((int64_t) reg[rs1(inst)] < (int64_t) imm_I(inst));

}

void CPU::exec_SLTIU(uint32_t inst){

    int64_t imm = (int64_t) imm_I(inst);

    reg[rd(inst)] = ((uint64_t) reg[rs1(inst)] < (uint64_t) imm);

}
void CPU::exec_XORI(uint32_t inst){
    int64_t imm = (int64_t) imm_I(inst);
    reg[rd(inst)] = reg[rs1(inst)] ^ imm;

}
void CPU::exec_SRLI(uint32_t inst){

    reg[rd(inst)] = (uint64_t) reg[rs1(inst)] >> shamt(inst);

}
void CPU::exec_SRAI(uint32_t inst){

    reg[rd(inst)] = (int64_t) reg[rs1(inst)] >> shamt(inst);

}
void CPU::exec_ORI(uint32_t inst){

    int64_t imm = (int64_t) imm_I(inst);
    reg[rd(inst)] = reg[rs1(inst)] | imm;

}
void CPU::exec_ANDI(uint32_t inst){

    int64_t imm = (int64_t) imm_I(inst);
    reg[rd(inst)] = reg[rs1(inst)] & imm;

}