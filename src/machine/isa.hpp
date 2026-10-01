#pragma once

#include <cstdint>

namespace RV32I
{
    // Major opcodes
    constexpr uint32_t OP_LUI    = 0x37;
    constexpr uint32_t OP_AUIPC  = 0x17;
    constexpr uint32_t OP_JAL    = 0x6F;
    constexpr uint32_t OP_JALR   = 0x67;
    constexpr uint32_t OP_BRANCH = 0x63;
    constexpr uint32_t OP_LOAD   = 0x03;
    constexpr uint32_t OP_STORE  = 0x23;
    constexpr uint32_t OP_IMM    = 0x13;
    constexpr uint32_t OP_REG    = 0x33;
    constexpr uint32_t OP_FENCE  = 0x0F;
    constexpr uint32_t OP_SYSTEM = 0x73;


    // R-type funct3
    constexpr uint32_t FUNCT3_ADD_SUB = 0x0;
    constexpr uint32_t FUNCT3_SLL     = 0x1;
    constexpr uint32_t FUNCT3_SLT     = 0x2;
    constexpr uint32_t FUNCT3_SLTU    = 0x3;
    constexpr uint32_t FUNCT3_XOR     = 0x4;
    constexpr uint32_t FUNCT3_SRL_SRA = 0x5;
    constexpr uint32_t FUNCT3_OR      = 0x6;
    constexpr uint32_t FUNCT3_AND     = 0x7;


    // R-type funct7
    constexpr uint32_t FUNCT7_ADD = 0x00;
    constexpr uint32_t FUNCT7_SUB = 0x20;
    constexpr uint32_t FUNCT7_SRL = 0x00;
    constexpr uint32_t FUNCT7_SRA = 0x20;
}