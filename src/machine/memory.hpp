#pragma once
#include <cstdint>
#include <vector>
class Memory{

    private:
            std::vector<uint8_t> mem;
    public:
            Memory(std::size_t size);
            uint8_t readByte(uint32_t addr) const;
            void writeByte(uint32_t addr, uint8_t value);
            uint32_t readWord(uint32_t addr) const;
            void writeWord(uint32_t addr, uint32_t value);
           
      
};