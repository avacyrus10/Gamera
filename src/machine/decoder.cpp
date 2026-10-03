#include "decoder.hpp"
#include "isa.hpp"
//delete
#include <iostream>

//delete
Instruction decode(uint32_t raw){
    std::cout << std::hex
              << "Decoder received: 0x" << raw
              << std::dec << '\n';

    Instruction instruction;
    instruction.opcode = raw & 0x7F;
    instruction.rd = (raw >> 7) & 0x1F;
    instruction.funct3 = (raw >> 12) & 0x7;
    instruction.rs1 = (raw >> 15) & 0x1F;
    instruction.rs2 = (raw >> 20) & 0x1F;
    instruction.funct7 = (raw >> 25) & 0x7F;
    uint32_t imm = (raw >> 20) & 0xFFF;

  if(instruction.opcode == RV32I::OP_LOAD ||
        instruction.opcode == RV32I::OP_IMM){

    if (imm & 0x800)
    {
        imm |= 0xFFFFF000;
    }
    instruction.immediate = imm; 
    instruction.immediate = static_cast<int32_t>(imm);       
        }
else if (instruction.opcode == RV32I::OP_STORE)
{
    uint32_t imm =
          ((raw >> 25) & 0x7F) << 5
        | ((raw >> 7) & 0x1F);

    if (imm & 0x800)
    {
        imm |= 0xFFFFF000;
    }

    instruction.immediate = static_cast<int32_t>(imm);
}
else if (instruction.opcode == RV32I::OP_BRANCH)
{
    uint32_t imm =
          ((raw >> 31) & 0x1) << 12
        | ((raw >> 25) & 0x3F) << 5
        | ((raw >> 8)  & 0xF)  << 1
        | ((raw >> 7)  & 0x1)  << 11;

    if (imm & 0x1000)
    {
        imm |= 0xFFFFE000;
    }

    instruction.immediate = static_cast<int32_t>(imm);
}        

    return instruction;
}