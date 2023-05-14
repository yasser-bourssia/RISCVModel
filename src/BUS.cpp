#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
#include "../includes/BUS.h"



uint64_t BUS::bus_load(uint64_t addr, uint64_t size){


dram.dram_load(addr, size);

}

void BUS::bus_store(uint64_t addr, uint64_t size, uint64_t value){

dram.dram_store(addr, size, value);

}