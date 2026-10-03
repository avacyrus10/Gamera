#include <iostream>
#include <iomanip>
#include <array>

#include "machine/memory.hpp"
#include "machine/pipeline.hpp"
#include "machine/alu.hpp"

int main()
{
    // -----------------------------
    // Machine state
    // -----------------------------

    Memory memory(1024);

    uint32_t pc = 0;

    std::array<uint32_t, 32> registers{};

    // x1 = 10
    // x2 = 20
    registers[1] = 10;
    registers[2] = 20;

    ALU alu;

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
        | 0x33;          // opcode

    std::cout << "Instruction: 0x"
              << std::hex << add
              << std::dec << '\n';

    // Put instruction into memory
    memory.writeWord(0, add);

    // -----------------------------
    // Create pipeline
    // -----------------------------

    Pipeline pipeline(
        pc,
        memory,
        registers,
        alu
    );

    // -----------------------------
    // Run all five stages
    // -----------------------------

    std::cout << "\n--- IF ---\n";
    pipeline.fetch();

    std::cout << "--- ID ---\n";
    pipeline.decode();

    std::cout << "--- EX ---\n";
    pipeline.execute();

    std::cout << "--- MEM ---\n";
    pipeline.memoryAccess();

    std::cout << "--- WB ---\n";
    pipeline.writeBack();

    // -----------------------------
    // Check final result
    // -----------------------------

    std::cout << "\nFinal register state:\n";

    std::cout << "x1 = " << registers[1] << '\n';
    std::cout << "x2 = " << registers[2] << '\n';
    std::cout << "x3 = " << registers[3] << '\n';

    // -----------------------------
    // Verify
    // -----------------------------

    if (registers[3] == 30)
    {
        std::cout << "\nTEST PASSED: x3 = 30\n";
    }
    else
    {
        std::cout << "\nTEST FAILED: expected x3 = 30\n";
    }

    return 0;
}