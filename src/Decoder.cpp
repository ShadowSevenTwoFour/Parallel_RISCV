#include "Decoder.h"
#include <string>

int32_t sign_extend(uint32_t val, int bits) {
    int32_t mask = 1 << (bits - 1);
    return (val ^ mask) - mask;
}

Instruction decode(uint32_t raw) {
    Instruction instr;
    instr.raw = std::to_string(raw);

    // Extract fields
    uint32_t opcode = raw & 0x7F;
    uint32_t rd     = (raw >> 7)  & 0x1F;
    uint32_t funct3 = (raw >> 12) & 0x07;
    uint32_t rs1    = (raw >> 15) & 0x1F;
    uint32_t rs2    = (raw >> 20) & 0x1F;
    uint32_t funct7 = (raw >> 25) & 0x7F;

    // Extract all immediates
    int32_t imm_i = sign_extend((raw >> 20) & 0xFFF, 12);
    int32_t imm_s = sign_extend(((raw >> 25) << 5) | ((raw >> 7) & 0x1F), 12);
    int32_t imm_b = sign_extend(((raw >> 31) << 12) |
                                (((raw >> 7) & 0x1) << 11) |
                                (((raw >> 25) & 0x3F) << 5) |
                                ((raw >> 8) & 0xF), 13);
    int32_t imm_u = static_cast<int32_t>(raw & 0xFFFFF000);
    int32_t imm_j = sign_extend(((raw >> 31) << 20) |
                                (((raw >> 12) & 0xFF) << 12) |
                                (((raw >> 20) & 0x1) << 11) |
                                ((raw >> 21) & 0x3FF), 21);

    instr.opcode = Opcode::UNKNOWN;
    instr.rd = rd;
    instr.rs1 = rs1;
    instr.rs2 = rs2;
    instr.imm = 0;

    switch (opcode) {
        case 0b0110011: // R-type
            if (funct3 == 0b000 && funct7 == 0b0000000) instr.opcode = Opcode::ADD;
            else if (funct3 == 0b000 && funct7 == 0b0100000) instr.opcode = Opcode::SUB;
            else if (funct3 == 0b111 && funct7 == 0b0000000) instr.opcode = Opcode::AND;
            else if (funct3 == 0b110 && funct7 == 0b0000000) instr.opcode = Opcode::OR;
            else if (funct3 == 0b100 && funct7 == 0b0000000) instr.opcode = Opcode::XOR;
            break;

        case 0b0010011: // I-type
            instr.imm = imm_i;
            if (funct3 == 0b000) instr.opcode = Opcode::ADDI;
            break;

        case 0b0000011: // Load (LW)
            instr.imm = imm_i;
            if (funct3 == 0b010) instr.opcode = Opcode::LW;
            break;

        case 0b0100011: // Store (SW)
            instr.imm = imm_s;
            if (funct3 == 0b010) instr.opcode = Opcode::SW;
            break;

        case 0b1100011: // Branch (BEQ, BNE)
            instr.imm = imm_b;
            if (funct3 == 0b000) instr.opcode = Opcode::BEQ;
            else if (funct3 == 0b001) instr.opcode = Opcode::BNE;
            break;

        default:
            instr.opcode = Opcode::UNKNOWN;
            break;
    }

    return instr;
}
