#include "Memory.h"
#include <cstring>


// set memory to zero on initialization
Memory::Memory(size_t size_bytes) {
    data = std::vector<uint8_t>(size_bytes, 0);
}

// safeguard for OOB access
void Memory::check_bounds(uint64_t addr, size_t access_size) const {
    if (addr + access_size > data.size()) {
        throw std::out_of_range("Memory access out of bounds");
    }
}

// load 64-bit double word from memory
int64_t Memory::load64(uint64_t addr) const {
    check_bounds(addr, sizeof(int64_t));
    int64_t val;
    std::memcpy(&val, &data[addr], sizeof(int64_t));
    return val;
}

// store 64-bit double word to memory
void Memory::store64(uint64_t addr, int64_t val) {
    check_bounds(addr, sizeof(int64_t));
    std::memcpy(&data[addr], &val, sizeof(int64_t));
}