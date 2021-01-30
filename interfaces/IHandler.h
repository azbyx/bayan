#pragma once

#include <memory>
#include <filesystem>

namespace bayan {

namespace fs = std::filesystem;

class IHandler {
public:
    virtual ~IHandler() {}

    virtual void addFile(const fs::path&, size_t) = 0;

};

using IHandlerUP = std::unique_ptr<IHandler>;
using IHandlerSP = std::shared_ptr<IHandler>;

} // namespace bayan
