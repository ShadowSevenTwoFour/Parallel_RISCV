 #pragma once
#include <cstdint>
#include <string>

enum class Opcode {
    ADD, SUB, ADDI,
    AND, OR, XOR,
    LW, SW,
    BEQ, BNE,
    UNKNOWN
};

struct Instruction {
    Opcode opcode;
    uint8_t rd = 0, rs1 = 0, rs2 = 0;
    int64_t imm = 0;
    std::string raw; // debug
};
