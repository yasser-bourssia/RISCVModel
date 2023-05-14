#include "../includes/memory.h"
#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

DRAM::DRAM(){

    memset(mem, 0, sizeof(uint8_t) * DRAM_SIZE);

}

uint64_t DRAM::dram_load(uint64_t addr, uint64_t size){

switch (size) {

    case 8:  return DRAM::dram_load_8(addr);  break;
        case 16: return DRAM::dram_load_16(addr); break;
        case 32: return DRAM::dram_load_32(addr); break;
        case 64: return DRAM::dram_load_64(addr); break;
        default: ;
    }
    return 1;


}


void DRAM::dram_store(uint64_t addr, uint64_t size, uint64_t value){

switch (size) {
        case 8:  DRAM::dram_store_8(addr, value);  break;
        case 16: DRAM::dram_store_16(addr, value); break;
        case 32: DRAM::dram_store_32(addr, value); break;
        case 64: DRAM::dram_store_64(addr, value); break;
        default: ;
    }

}

uint64_t DRAM::dram_load_8(uint64_t addr){


    uint64_t value;

    value = mem[addr - DRAM_BASE];

    return value;

}


uint64_t DRAM::dram_load_16(uint64_t addr){


    uint64_t value;

    value = mem[addr - DRAM_BASE]
     |  mem[addr - DRAM_BASE + 1] << 8; 
    return value;
    
}


uint64_t DRAM::dram_load_32(uint64_t addr){


    uint64_t value;

    value = mem[addr - DRAM_BASE]
     |  mem[addr - DRAM_BASE + 1] << 8
     |  mem[addr - DRAM_BASE + 2] << 16
     |  mem[addr - DRAM_BASE + 3] << 24;

    return value;
    
}


uint64_t DRAM::dram_load_64(uint64_t addr){

    uint64_t value;

    value = mem[addr - DRAM_BASE]
     |  mem[addr - DRAM_BASE + 1] << 8
     |  mem[addr - DRAM_BASE + 2] << 16
     |  mem[addr - DRAM_BASE + 3] << 24
     |  mem[addr - DRAM_BASE + 4] << 32
     |  mem[addr - DRAM_BASE + 5] << 40
     |  mem[addr - DRAM_BASE + 6] << 48
     |  mem[addr - DRAM_BASE + 7] << 56;

    return value;

    
}


void DRAM::dram_store_8(uint64_t addr, uint64_t value){

    mem[addr - DRAM_BASE] = value;


}


void DRAM::dram_store_16(uint64_t addr, uint64_t value){

    mem[addr - DRAM_BASE] = (value & 0xff);
    mem[addr - DRAM_BASE + 1] = (value >> 8) & 0xff;
    
    
}


void DRAM::dram_store_32(uint64_t addr, uint64_t value){
    mem[addr - DRAM_BASE] = value & 0xff;
    mem[addr - DRAM_BASE + 1] = (value >> 8) & 0xff;
    mem[addr - DRAM_BASE + 2] = (value >> 16) & 0xff;
    mem[addr - DRAM_BASE + 3] = (value >> 24) & 0xff;
    
}


void DRAM::dram_store_64(uint64_t addr, uint64_t value){
    mem[addr - DRAM_BASE] = value & 0xff;
    mem[addr - DRAM_BASE + 1] = (value >> 8) & 0xff;
    mem[addr - DRAM_BASE + 2] = (value >> 16) & 0xff;
    mem[addr - DRAM_BASE + 3] = (value >> 24) & 0xff;
    mem[addr - DRAM_BASE + 4] = (value >> 32) & 0xff;
    mem[addr - DRAM_BASE + 5] = (value >> 40) & 0xff;
    mem[addr - DRAM_BASE + 6] = (value >> 48) & 0xff;
    mem[addr - DRAM_BASE + 7] = (value >> 56) & 0xff;

}

