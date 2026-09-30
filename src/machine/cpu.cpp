#include "cpu.hpp"

CPU::CPU()
    : pc(0), registers{}
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
            registers[index] = value;
    }
