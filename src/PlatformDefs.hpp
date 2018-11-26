#pragma once

#include <climits>

namespace defs {

constexpr auto CHARBITS = sizeof(char) * CHAR_BIT;
constexpr unsigned int BYTES_PER_WORD = 2;
//Least significant byte index in a word [0 => MSB, 1 => LSB]
constexpr auto LSB_IDX = 1;

} // namespace defs
