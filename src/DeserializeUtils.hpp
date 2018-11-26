#pragma once

#include "Field.hpp"
#include "PlatformDefs.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

namespace deserialize {

/**
 * A word contains most significant byte of the value the first and the least significant byte second.
 * This method swaps pairs of bytes.
 *
 * @param rBufferP Reference to byte-stream buffer
 */
static void hostByteOrder(std::vector<char>& rBufferP)
{
    // Leave the last byte alone if buffer size is odd (@TODO: Is this correct behavior?)
    const bool even = (rBufferP.size() % 2  == 0);
    auto endItr = even ? rBufferP.end() : std::prev(rBufferP.end());

    for (auto it = rBufferP.begin(); it != endItr; std::advance(it, 2))
    {
        std::swap(*it, *(std::next(it)));
    }
}

/**
 * Reads bytes from field @a rFieldP in file stream @a rStreamP into buffer @a rBufferP
 * Also converts the bytes to host byte order
 */
static void readBytes(std::ifstream& rStreamP, const ata::Field& rFieldP, std::vector<char>& rBufferP)
{
    rStreamP.seekg(rFieldP.startWordM * defs::BYTES_PER_WORD, std::ios_base::beg);

    auto numBytes = rFieldP.span() * defs::BYTES_PER_WORD;
    rBufferP.resize(numBytes);

    auto count = rStreamP.get(rBufferP.data(), numBytes + 1).gcount();
    assert(static_cast<size_t>(count) == numBytes);

    hostByteOrder(rBufferP);
}

} // namespace deserialize
