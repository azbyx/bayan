#pragma once

#include <string>
#include <memory>

namespace bayan {

class IHash {
public:
    virtual ~IHash() {}

    virtual std::string hashAsString(const char*, size_t) = 0;

};

using IHashSP = std::shared_ptr<IHash>;

} // namespace bayan
