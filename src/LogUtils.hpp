#pragma once

#include "PlatformDefs.hpp"

#include <bitset>
#include <iostream>
#include <vector>

namespace log {

/** Prints contents of @a rBufferP to stdout */
static void printBuffer(const char* pTagP, const std::vector<char>& rBufferP)
{
    std::cout << pTagP << std::endl;
    for (const auto& item: rBufferP)
    {
        std::cout << item;
    }
    std::cout << std::endl << std::endl << std::flush;
}

/** Prints contents of @a rBufferP to stdout as binary text */
static void printBinary(const char* pTagP, const std::vector<char>& rBufferP)
{
    std::cout << pTagP << std::endl;
    for (const auto& item: rBufferP)
    {
        std::bitset<defs::CHARBITS> bits(item);
        std::cout << bits << ' ';
    }
    std::cout << std::endl << std::endl << std::flush;
}

} // namespace log
