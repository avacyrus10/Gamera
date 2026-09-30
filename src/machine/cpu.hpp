#pragma once
#include <array>
#include <cstdint>
#include "instruction.hpp"
#include "memory.hpp"
class CPU{

    private:
            std::array<uint32_t,32> registers;
            uint32_t pc;
            Memory& memory;
    public:

            CPU(Memory& memory);
            uint32_t getPC() const;
            void setPC(uint32_t value);

            uint32_t getRegister(std::size_t index) const;
            void setRegister(std::size_t index, uint32_t value);

            void execute(const Instruction instruction);

            uint32_t fetch() const;




};