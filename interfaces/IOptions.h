#pragma once

#include <memory>
#include <filesystem>
#include "typesBayan.h"

namespace bayan {


class IOptions {

public:
    using path = std::filesystem::path;

    virtual ~IOptions() {}

    virtual std::string getHashOfBuffer(const char*) = 0;

    virtual size_t getBlockSize() const = 0;

    virtual size_t getMinFileSize() const = 0;

    virtual long getLevelScanning() const = 0;

    virtual std::vector<path> getIncludePaths() const = 0;

    virtual std::vector<path> getExcludePaths() const = 0;

    virtual std::vector<Mask> getMasks() const = 0;

    virtual void printOpt() = 0;

};

using IOptionsUP = std::unique_ptr<IOptions>;
using IOptionsSP = std::shared_ptr<IOptions>;

} // namespace bayan
