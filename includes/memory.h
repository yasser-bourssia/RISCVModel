#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>

#define DRAM_SIZE 1024 * 1024 * 1
#define DRAM_BASE 0x800000000


class DRAM{

uint8_t mem[DRAM_SIZE];



public:

DRAM();

// Loading from DRAM functions.

uint64_t dram_load(uint64_t addr, uint64_t size);
uint64_t dram_load_8(uint64_t addr);
uint64_t dram_load_16(uint64_t addr);
uint64_t dram_load_32(uint64_t addr);
uint64_t dram_load_64(uint64_t addr);


// Storing in the DRAM functions.

void dram_store(uint64_t addr, uint64_t size, uint64_t value);
void dram_store_8(uint64_t addr, uint64_t value);
void dram_store_16(uint64_t addr, uint64_t value);
void dram_store_32(uint64_t addr, uint64_t value);
void dram_store_64(uint64_t addr, uint64_t value);


};