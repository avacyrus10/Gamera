#pragma once
#include <cstdint>
#include "memory.hpp"
#include "instruction.hpp"
#include <array>

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

class Pipeline
{
    private:
        uint32_t &pc;
        Memory& memory;
        IF_ID if_id;
        ID_EX id_ex;
        std::array<uint32_t, 32>& registers;

    public:
        Pipeline(uint32_t &pc, Memory& memory, std::array<uint32_t, 32>& registers);
        void fetch();
        void decode();

        const ID_EX& getID_EX() const;

};
