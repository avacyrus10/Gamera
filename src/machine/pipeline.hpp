#pragma once
#include <cstdint>
#include "memory.hpp"
#include "instruction.hpp"
#include <array>
#include "alu.hpp"
struct IF_ID
{   
    uint32_t pc;
    uint32_t instruction;
};
struct ID_EX
{
    uint32_t pc;
    Instruction instruction;

    uint32_t rs1_value;
    uint32_t rs2_value;
};
struct EX_MEM
{
    uint32_t pc;
    Instruction instruction;
    uint32_t result;
    uint32_t storeResult;
};
struct MEM_WB
{
    uint32_t pc;
    Instruction instruction;
    uint32_t result;
};


class Pipeline
{
    private:
        uint32_t &pc;
        Memory& memory;
        IF_ID if_id;
        ID_EX id_ex;
        EX_MEM ex_mem;
        MEM_WB mem_wb;
        std::array<uint32_t, 32>& registers;
        ALU& alu;

    public:
        Pipeline(uint32_t &pc, Memory& memory, std::array<uint32_t, 32>& registers, ALU& alu);
        void fetch();
        void decode();
        void execute();
        void memoryAccess();
        void writeBack();

        const ID_EX& getID_EX() const;

};
