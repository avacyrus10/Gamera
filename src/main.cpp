#include <iostream>

#include "machine/cpu.hpp"
#include "machine/decoder.hpp"
#include "machine/memory.hpp"

int main()
{
    Memory memory(1024);
    CPU cpu(memory);

    uint32_t add =
          (0x00 << 25)
        | (2    << 20)
        | (1    << 15)
        | (0x0  << 12)
        | (3    << 7)
        | 0x33;

    memory.writeWord(0, add);

    uint32_t raw = cpu.fetch();

    Instruction instruction = decode(raw);

    std::cout << "opcode: " << static_cast<int>(instruction.opcode) << '\n';
    std::cout << "rd: " << static_cast<int>(instruction.rd) << '\n';
    std::cout << "rs1: " << static_cast<int>(instruction.rs1) << '\n';
    std::cout << "rs2: " << static_cast<int>(instruction.rs2) << '\n';
}