#include <iostream>

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

    return 0;
}