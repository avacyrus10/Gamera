#include "alu.hpp"


    uint32_t ALU::add(uint32_t a, uint32_t b){
        return a + b;
    }
    uint32_t ALU::sub(uint32_t a, uint32_t b){
        return a - b;
    }
    uint32_t ALU::bitwiseOr(uint32_t a, uint32_t b){
        return a | b;
    }
    uint32_t ALU::bitwiseAnd(uint32_t a, uint32_t b){
        return a & b;
    }
    uint32_t ALU::bitwiseXor(uint32_t a, uint32_t b){
        return a ^ b;
    }                

