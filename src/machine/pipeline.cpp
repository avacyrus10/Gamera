#include "pipeline.hpp"
#include "decoder.hpp"

Pipeline::Pipeline(uint32_t &pc, Memory& memory, std::array<uint32_t, 32>& registers)
    :pc(pc), memory(memory), registers(registers)
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