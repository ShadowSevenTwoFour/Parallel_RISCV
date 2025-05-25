#include "Decoder.h"
#include <iostream>

std::string opcode_to_str(Opcode op) {
    switch (op) {
        case Opcode::ADD:  return "ADD";
        case Opcode::SUB:  return "SUB";
        case Opcode::ADDI: return "ADDI";
        case Opcode::AND:  return "AND";
        case Opcode::OR:   return "OR";
        case Opcode::XOR:  return "XOR";
        case Opcode::LW:   return "LW";
        case Opcode::SW:   return "SW";
        case Opcode::BEQ:  return "BEQ";
        case Opcode::BNE:  return "BNE";
        default:           return "UNKNOWN";
    }
}

void print(const Instruction& instr) {
    std::cout << "Decoded Instruction:\n";
    std::cout << "  Opcode: " << opcode_to_str(instr.opcode) << "\n";
    std::cout << "  rd:     x" << +instr.rd << "\n";
    std::cout << "  rs1:    x" << +instr.rs1 << "\n";
    std::cout << "  rs2:    x" << +instr.rs2 << "\n";
    std::cout << "  imm:    " << instr.imm << "\n";
    std::cout << "  raw:    " << instr.raw << "\n";
}

int main() {
    uint32_t addi_x1_x0_5 = 0x00500093;  // ADDI x1, x0, 5
    uint32_t add_x3_x1_x2 = 0x002081B3;  // ADD x3, x1, x2

    Instruction i1 = decode(addi_x1_x0_5);
    Instruction i2 = decode(add_x3_x1_x2);

    print(i1);
    print(i2);

    return 0;
}
