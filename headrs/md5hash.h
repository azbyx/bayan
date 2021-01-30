#pragma once

#include "IHash.h"

namespace bayan {

/**
    \brief Class for counting md5.
*/
class Md5Hash : public IHash {

public:
    std::string hashAsString(const char*, size_t);

};


} // namespace bayan
