#include "cpu.hpp"
#include <stdexcept>
#include "isa.hpp"
#include "alu.hpp"
#include "pipeline.hpp"

CPU::CPU(Memory& memory)
    : pc(0), registers{}, memory(memory), alu{}, pipeline{pc, memory, registers}
{

}

    uint32_t CPU::getPC() const{
        return pc;
    }
    void CPU::setPC(uint32_t value){
            pc = value;
    }
    uint32_t CPU::getRegister(std::size_t index) const{
        return registers[index];
    }
    void CPU::setRegister(std::size_t index, uint32_t value){
            if(index >= registers.size()){
                throw std::out_of_range("register index out of range");
            }
            if(index == 0){
                value = 0;
            }
            registers[index] = value;
    }

    void CPU::execute(const Instruction& instruction){

        switch (instruction.opcode)
        {
            case RV32I::OP_REG:
                {
                    uint32_t rs1 = getRegister(instruction.rs1);
                    uint32_t rs2 = getRegister(instruction.rs2);

                if(instruction.funct3 == RV32I::FUNCT3_ADD_SUB &&
                     instruction.funct7 == RV32I::FUNCT7_ADD){

                    uint32_t result = alu.add(rs1, rs2);
                    setRegister(instruction.rd, result);

                }
                else if(instruction.funct3 == RV32I::FUNCT3_ADD_SUB &&
                     instruction.funct7 == RV32I::FUNCT7_SUB){
                    uint32_t rs1 = getRegister(instruction.rs1);
                    uint32_t rs2 = getRegister(instruction.rs2);

                    uint32_t result = alu.sub(rs1, rs2);
                    setRegister(instruction.rd, result);


                }
                else if(instruction.funct3 == RV32I::FUNCT3_AND){
                    uint32_t rs1 = getRegister(instruction.rs1);
                    uint32_t rs2 = getRegister(instruction.rs2);

                    uint32_t result = alu.bitwiseAnd(rs1, rs2);
                    setRegister(instruction.rd, result);


                } 
                else if(instruction.funct3 == RV32I::FUNCT3_OR){
                    uint32_t rs1 = getRegister(instruction.rs1);
                    uint32_t rs2 = getRegister(instruction.rs2);

                    uint32_t result = alu.bitwiseOr(rs1, rs2);
                    setRegister(instruction.rd, result);


                }  
                else if(instruction.funct3 == RV32I::FUNCT3_XOR){
                    uint32_t rs1 = getRegister(instruction.rs1);
                    uint32_t rs2 = getRegister(instruction.rs2);

                    uint32_t result = alu.bitwiseXor(rs1, rs2);
                    setRegister(instruction.rd, result);

                }
                }
                break;
            case RV32I::OP_IMM:
                {
                uint32_t rs1 = (instruction.rs1);

                if(instruction.funct3 == RV32I::FUNCT3_ADD_SUB){
                    uint32_t result = alu.add(rs1, static_cast<uint32_t>(instruction.immediate));
                    setRegister(instruction.rd, result);
                }  
                else if(instruction.funct3 == RV32I::FUNCT3_XOR){
                    uint32_t result = alu.bitwiseXor(rs1, static_cast<uint32_t>(instruction.immediate));
                    setRegister(instruction.rd, result);
                }  
                else if(instruction.funct3 == RV32I::FUNCT3_OR){
                    uint32_t result = alu.bitwiseOr(rs1, static_cast<uint32_t>(instruction.immediate));
                    setRegister(instruction.rd, result);
                }  
                else if(instruction.funct3 == RV32I::FUNCT3_AND){
                    uint32_t result = alu.bitwiseAnd(rs1, static_cast<uint32_t>(instruction.immediate));
                    setRegister(instruction.rd, result);
                }  
                break;  
            }
            case RV32I::OP_LOAD:
            {
                uint32_t base = getRegister(instruction.rs1);
                uint32_t offset = static_cast<uint32_t>(instruction.immediate);

                if(instruction.funct3 == RV32I::FUNCT3_LW){
                    uint32_t address = alu.add(base, offset);
                    uint32_t result = memory.readWord(address);
                    setRegister(instruction.rd, result);
                }
                break;
            } 
            case RV32I::OP_STORE:
            {
                uint32_t base = getRegister(instruction.rs1);
                uint32_t value = getRegister(instruction.rs2);
                uint32_t offset = static_cast<uint32_t>(instruction.immediate);

                uint32_t address = alu.add(base, offset);
                memory.writeWord(address, value);
                
                break;
            }                                                                                                                            
        }
    }

