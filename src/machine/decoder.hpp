#pragma once

#include <cstdint>
#include "instruction.hpp"

Instruction decode(uint32_t raw);