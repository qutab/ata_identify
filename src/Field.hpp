#pragma once

#include <cassert>

namespace ata {

/**
 * Data structure representing a field in ATA IDENTIFY response.
 * A field can contain one or more words.
 * Field is a non-polymorphic struct which is copy-constructible and copy-assignable.
 */
struct Field final
{
    /**
     * Construct Field with multiple words
     *
     * @param startP Number of first word for the field
     * @param endP Number of last word for the field
     */
    Field(unsigned int startP, unsigned int endP)
      : startWordM(startP), endWordM(endP)
    {
        assert(startP <= endP);
    }

    /**
     * Construct Field with one word beginning at @wordP
     */
    explicit Field(unsigned int wordP)
      : startWordM(wordP), endWordM(wordP)
    {
    }

    /** Destructor */
    ~Field() = default;

    /** @return number of words in the inclusive range [startWordM - endWordM] */
    unsigned int span() const
    {
        return endWordM - startWordM + 1;
    }

    const unsigned int startWordM;
    const unsigned int endWordM;
};

} // namespace ata
