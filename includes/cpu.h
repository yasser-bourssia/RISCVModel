#include <iostream>
#include "BUS.h"
#include "opcodes.h"
using namespace std;


class CPU{

        /*

    0 	- 	x0 	zero 	hardwired zero 	-
    1 	- 	x1 	ra 	return address 	-R
    2 	- 	x2 	sp 	stack pointer 	-E
    3 	- 	x3 	gp 	global pointer 	-
    4 	- 	x4 	tp 	thread pointer 	-
    5 	- 	x5 	t0 	temporary register 0 	-R
    6 	- 	x6 	t1 	temporary register 1 	-R
    7 	- 	x7 	t2 	temporary register 2 	-R
    8 	0 	x8 	s0 / fp 	saved register 0 / frame pointer 	-E
    9 	1 	x9 	s1 	saved register 1 	-E
    10 	2 	x10 	a0 	function argument 0 / return value 0 	-R
    11 	3 	x11 	a1 	function argument 1 / return value 1 	-R
    12 	4 	x12 	a2 	function argument 2 	-R
    13 	5 	x13 	a3 	function argument 3 	-R
    14 	6 	x14 	a4 	function argument 4 	-R
    15 	7 	x15 	a5 	function argument 5 	-R
    16 	- 	x16 	a6 	function argument 6 	-R
    17 	- 	x17 	a7 	function argument 7 	-R
    18 	- 	x18 	s2 	saved register 2 	-E
    19 	- 	x19 	s3 	saved register 3 	-E
    20 	- 	x20 	s4 	saved register 4 	-E
    21 	- 	x21 	s5 	saved register 5 	-E
    22 	- 	x22 	s6 	saved register 6 	-E
    23 	- 	x23 	s7 	saved register 7 	-E
    24 	- 	x24 	s8 	saved register 8 	-E
    25 	- 	x25 	s9 	saved register 9 	-E
    26 	- 	x26 	s10 	saved register 10 	-E
    27 	- 	x27 	s11 	saved register 11 	-E
    28 	- 	x28 	t3 	temporary register 3 	-R
    29 	- 	x29 	t4 	temporary register 4 	-R
    30 	- 	x30 	t5 	temporary register 5 	-R
    31 	- 	x31 	t6 	temporary register 6 	-R 

    */

    private:

        uint64_t reg[32]; 
        uint64_t pc_reg;
        BUS bus;

    public:


        CPU();


        void ResetCPU();

        void incrementPC();

        uint32_t cpu_fetch();

        int cpu_execute(uint32_t inst);


        void dump_registers();

        // ---------------- Instruction exec functions -------------------------------
        
        // I-type instructions -----

        void exec_ADDI(uint32_t inst);
        void exec_SLLI(uint32_t inst);
        void exec_SLTI(uint32_t inst);
        void exec_SLTIU(uint32_t inst);
        void exec_XORI(uint32_t inst);
        void exec_SRLI(uint32_t inst);
        void exec_SRAI(uint32_t inst);
        void exec_ORI(uint32_t inst);
        void exec_ANDI(uint32_t inst);


    private:
        uint64_t cpu_load(uint64_t addr, uint64_t size);
        uint64_t cpu_store(uint64_t addr, uint64_t data, uint64_t size);





};