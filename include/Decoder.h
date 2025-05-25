#pragma once
#include "ISA.h"
#include <cstdint>

Instruction decode(uint32_t raw); // Barely need anything here its really just instantiating the decode function, and having it return an Instruction

