#include "memory.hpp"
#include <stdexcept>
Memory::Memory(std::size_t size)
    : mem(size)
{

}
    void Memory::writeByte(uint32_t addr, u_int8_t value) {
        if(addr  >= mem.size()){
            throw std::out_of_range("memory address out of range!");
        }
        mem[addr] = value;
    }
    u_int8_t Memory::readByte(uint32_t addr) const{
        if(addr >= mem.size()){
            throw std::out_of_range("memory address out of range!");
        }
        return mem[addr];
    }
    uint32_t Memory::readWord(uint32_t addr) const
{
    if (addr + 3 >= mem.size()) {
        throw std::out_of_range("memory address out of range!");
    }

    return static_cast<uint32_t>(mem[addr])
         | (static_cast<uint32_t>(mem[addr + 1]) << 8)
         | (static_cast<uint32_t>(mem[addr + 2]) << 16)
         | (static_cast<uint32_t>(mem[addr + 3]) << 24);
}   
    void Memory::writeWord(uint32_t addr, uint32_t value){
        if(addr + 3 >= mem.size()){
            throw std::out_of_range("memory address out of range!");
        }

        mem[addr]     = static_cast<uint8_t>(value);
        mem[addr + 1] = static_cast<uint8_t>(value >> 8);
        mem[addr + 2] = static_cast<uint8_t>(value >> 16);
        mem[addr + 3] = static_cast<uint8_t>(value >> 24);
    }
