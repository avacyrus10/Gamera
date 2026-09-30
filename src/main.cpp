#include <iostream>
#include "machine/memory.hpp"

#include "machine/cpu.hpp"

int main()
{
    CPU cpu;

    std::cout << "PC: " << cpu.getPC() << '\n';
    std::cout << "R0: " << cpu.getRegister(0) << '\n';

    cpu.setPC(100);
    cpu.setRegister(5, 42);

    std::cout << "PC: " << cpu.getPC() << '\n';
    std::cout << "R5: " << cpu.getRegister(5) << '\n';

    Memory memory(1024);

memory.writeWord(100, 0x12345678);

std::cout << std::hex << memory.readWord(100) << '\n';

    return 0;
}