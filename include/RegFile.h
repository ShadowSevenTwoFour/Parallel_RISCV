#pragma once
#include <array>
#include <cstdint>

#define NUM_REGS 32

class RegFile {
public:
    RegFile();
    int64_t& operator[](int idx);
    const int64_t& operator[](int idx) const;

private:
    std::array<int64_t, NUM_REGS> regs;
    int64_t zero = 0;
};