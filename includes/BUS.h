#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
#include "memory.h"

// This class represents the BUS going from the DRAM to the CPU and viceversa.

class BUS {

DRAM dram;


public:


uint64_t bus_load(uint64_t addr, uint64_t size);

void bus_store(uint64_t addr, uint64_t size, uint64_t value);


};