#include "cpu.hpp"
#include <stdexcept>
#include "isa.hpp"
#include "alu.hpp"
#include "pipeline.hpp"

CPU::CPU(Memory& memory)
    : pc(0), registers{}, memory(memory), alu{}, pipeline{pc, memory, registers, alu}
{

}

    uint32_t CPU::getPC() const{
        return pc;
    }
    void CPU::setPC(uint32_t value){
            pc = value;
    }
    uint32_t CPU::getRegister(std::size_t index) const{
        return registers[index];
    }
    void CPU::setRegister(std::size_t index, uint32_t value){
            if(index >= registers.size()){
                throw std::out_of_range("register index out of range");
            }
            if(index == 0){
                value = 0;
            }
            registers[index] = value;
    }



