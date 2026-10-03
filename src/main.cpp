#include <iostream>
#include <iomanip>
#include <array>
#include <iostream>
#include "machine/memory.hpp"
#include "machine/pipeline.hpp"

int main()
{
    
    // -----------------------------
    // Create machine state
    // -----------------------------

    Memory memory(1024);

    uint32_t pc = 0;

    std::array<uint32_t, 32> registers{};

    // Give x1 and x2 some values
    registers[1] = 10;
    registers[2] = 20;

    // -----------------------------
    // Encode:
    // ADD x3, x1, x2
    // -----------------------------

    uint32_t add =
          (0x00 << 25)   // funct7
        | (2    << 20)   // rs2 = x2
        | (1    << 15)   // rs1 = x1
        | (0x0  << 12)   // funct3
        | (3    << 7)    // rd = x3
        | 0x33;           // opcode


    // Put instruction into memory at address 0
    memory.writeWord(0, add);

    // -----------------------------
    // Create pipeline
    // -----------------------------

    Pipeline pipeline(pc, memory, registers);

    // -----------------------------
    // IF stage
    // -----------------------------

    pipeline.fetch();

    // -----------------------------
    // ID stage
    // -----------------------------

    pipeline.decode();

    // -----------------------------
    // Inspect ID/EX
    // -----------------------------

    const ID_EX& id_ex = pipeline.getID_EX();

    std::cout << "ID/EX contents:\n";

    std::cout << "PC: "
              << id_ex.pc
              << '\n';

    std::cout << "rs1: x"
              << static_cast<int>(id_ex.instruction.rs1)
              << '\n';

    std::cout << "rs2: x"
              << static_cast<int>(id_ex.instruction.rs2)
              << '\n';

    std::cout << "rd: x"
              << static_cast<int>(id_ex.instruction.rd)
              << '\n';

    std::cout << "rs1 value: "
              << id_ex.rs1_value
              << '\n';

    std::cout << "rs2 value: "
              << id_ex.rs2_value
              << '\n';

    return 0;
}