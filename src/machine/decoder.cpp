#include "decoder.hpp"
#include "isa.hpp"
Instruction decode(uint32_t raw){

    Instruction instruction;
    instruction.opcode = raw & 0x7F;
    instruction.rd = (raw >> 7) & 0x1F;
    instruction.funct3 = (raw >> 12) & 0x7;
    instruction.rs1 = (raw >> 15) & 0x1F;
    instruction.rs2 = (raw >> 20) & 0x1F;
    instruction.funct7 = (raw >> 25) & 0x7F;
    uint32_t imm = (raw >> 20) & 0xFFF;

  if(instruction.opcode == RV32I::FUNCT3_LW ||
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

    return instruction;
}