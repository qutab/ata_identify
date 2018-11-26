#pragma once

#include "PlatformDefs.hpp"

#include <cassert>
#include <iostream>

namespace ata {
/** @return whether the bit at @a positionP in @a byteP set */
static bool getBit(char byteP, unsigned int positionP)
{
    assert(positionP <= defs::CHARBITS - 1);
    return (byteP >> positionP) & 0x1;
}

/** Parse ULTRA DMA Mode support */
static void parseUltraDmaModeSupport(char modeP)
{
    const unsigned int DMA_MSB_BIT = 6;
    for (unsigned int i = DMA_MSB_BIT + 1; i-- > 0;)
    {
        if (getBit(modeP, i))
        {
            std::cout << "Ultra DMA mode " << i << " and below supported.";
            std::cout << std::endl << std::endl << std::flush;
            break;
        }
    }
}

/** Parse Smart self test support */
static void parseSmartStSupport(char stWord84P, char stWord87P)
{
    const unsigned int ST_BIT = 1;
    if (getBit(stWord84P, ST_BIT) or getBit(stWord87P, ST_BIT))
    {
        std::cout << "Smart self test is supported." << std::endl << std::flush;
    }
}

} // namespace ata
