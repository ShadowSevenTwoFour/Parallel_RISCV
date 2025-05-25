#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>

class Memory {
public:
    Memory(size_t size_bytes);

    int64_t load64(uint64_t addr) const;
    void store64(uint64_t addr, int64_t val);

private:
    std::vector<uint8_t> data;
    void check_bounds(uint64_t addr, size_t access_size) const;
};