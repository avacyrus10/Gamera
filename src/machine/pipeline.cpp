#include "pipeline.hpp"
#include "decoder.hpp"
#include "isa.hpp"
Pipeline::Pipeline(uint32_t &pc, Memory& memory, std::array<uint32_t, 32>& registers, ALU& alu)
    :pc(pc), memory(memory), registers(registers), alu(alu)
{

}

void Pipeline::fetch(){
    if_id.pc = pc;
    if_id.instruction = memory.readWord(pc);

    pc+=4;
}

void Pipeline::decode(){
    uint32_t raw = if_id.instruction;
    Instruction instruction = ::decode(raw);

    id_ex.pc = if_id.pc;
    id_ex.instruction = instruction;
    
    id_ex.rs1_value = registers[instruction.rs1];
    id_ex.rs2_value = registers[instruction.rs2];


}

const ID_EX& Pipeline::getID_EX() const
{
    return id_ex;
}
 void Pipeline::execute(){


        switch (id_ex.instruction.opcode)
        {
            case RV32I::OP_REG:
                
                if(id_ex.instruction.funct3 == RV32I::FUNCT3_ADD_SUB &&
                     id_ex.instruction.funct7 == RV32I::FUNCT7_ADD){

                    uint32_t result = alu.add(id_ex.rs1_value, id_ex.rs2_value);
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result;

                }
                else if(id_ex.instruction.funct3 == RV32I::FUNCT3_ADD_SUB &&
                     id_ex.instruction.funct7 == RV32I::FUNCT7_SUB){

                    uint32_t result = alu.sub(id_ex.rs1_value, id_ex.rs2_value);
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result;                    


                }
                else if(id_ex.instruction.funct3 == RV32I::FUNCT3_AND){

                    uint32_t result = alu.bitwiseAnd(id_ex.rs1_value, id_ex.rs2_value);
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result; 

                } 
                else if(id_ex.instruction.funct3 == RV32I::FUNCT3_OR){

                    uint32_t result = alu.bitwiseOr(id_ex.rs1_value, id_ex.rs2_value);

                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result; 

                }  
                else if(id_ex.instruction.funct3 == RV32I::FUNCT3_XOR){

                    uint32_t result = alu.bitwiseXor(id_ex.rs1_value, id_ex.rs2_value);
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result; 

                }
                break;
            case RV32I::OP_IMM:
                {
                uint32_t rs1 = (id_ex.rs1_value);

                if(id_ex.instruction.funct3 == RV32I::FUNCT3_ADD_SUB){
                    uint32_t result = alu.add(rs1, static_cast<uint32_t>(id_ex.instruction.immediate));
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result;
                                }  
                else if(id_ex.instruction.funct3 == RV32I::FUNCT3_XOR){
                    uint32_t result = alu.bitwiseXor(rs1, static_cast<uint32_t>(id_ex.instruction.immediate));
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result;
                                }  
                else if(id_ex.instruction.funct3 == RV32I::FUNCT3_OR){
                    uint32_t result = alu.bitwiseOr(rs1, static_cast<uint32_t>(id_ex.instruction.immediate));
                    
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result;                   
                }  
                else if(id_ex.instruction.funct3 == RV32I::FUNCT3_AND){
                    uint32_t result = alu.bitwiseAnd(rs1, static_cast<uint32_t>(id_ex.instruction.immediate));
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result;                }  
                break;  
            }
            case RV32I::OP_LOAD:
            {
                uint32_t base = id_ex.rs1_value;
                uint32_t offset = static_cast<uint32_t>(id_ex.instruction.immediate);

                if(id_ex.instruction.funct3 == RV32I::FUNCT3_LW){
                    uint32_t address = alu.add(base, offset);
                    uint32_t result = address;
                    ex_mem.instruction = id_ex.instruction;
                    ex_mem.pc = id_ex.pc;
                    ex_mem.result = result;                 }
                break;
            } 
            case RV32I::OP_STORE:
            {
                uint32_t base = id_ex.rs1_value;
                uint32_t value = id_ex.rs2_value;
                uint32_t offset = static_cast<uint32_t>(id_ex.instruction.immediate);

                uint32_t address = alu.add(base, offset);
                uint32_t result = address; 
                ex_mem.storeResult = id_ex.rs2_value;  
                ex_mem.result = address;             
                break;
            }                                                                                                                            
        }
    }
void Pipeline::memoryAccess(){

    mem_wb.pc = ex_mem.pc;
    mem_wb.instruction = ex_mem.instruction;

    switch (ex_mem.instruction.opcode)
    {
    case RV32I::OP_LOAD:
            {
                if(ex_mem.instruction.funct3 == RV32I::FUNCT3_LW){
                    mem_wb.result = memory.readWord(ex_mem.result);
                }

                break;

            }
    case RV32I::OP_STORE:
    {
        if(ex_mem.instruction.funct3 == RV32I::OP_STORE){
            memory.writeWord(ex_mem.result, ex_mem.result);
        }
    }        

        break;
    
    
    default:
    {
            mem_wb.result = ex_mem.result;
    
        break;  
         }
    }
}
void Pipeline::writeBack(){

    switch (mem_wb.instruction.opcode)
    {
    case RV32I::OP_REG:
    case RV32I::OP_IMM:
    case RV32I::OP_LOAD:    
        {
            uint32_t rd = mem_wb.instruction.rd;
            if( rd != 0){
                registers[rd] = mem_wb.result;
            }
            break;
        }
        
    case RV32I::OP_STORE:
        

    
    default:
        break;
    }
}