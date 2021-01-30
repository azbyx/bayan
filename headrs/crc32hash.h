#pragma once

#include "IHash.h"

namespace bayan {

/**
    \brief Class for counting Crc32.
*/
class Crc32Hash : public IHash {

public:
    std::string hashAsString(const char*, size_t);

};


} // namespace bayan
