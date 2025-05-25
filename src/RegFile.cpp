#include "RegFile.h"

// Init all registers to zero 
RegFile::RegFile() {
    regs.fill(0);
}

// For mutable access
int64_t& RegFile::operator[](int idx) {
    if (idx == 0) return zero;
    return regs[idx];
}

// For read-only access
const int64_t& RegFile::operator[](int idx) const {
    if (idx == 0) return zero;
    return regs[idx];
}