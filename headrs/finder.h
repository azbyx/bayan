#pragma once

#include <vector>
#include "IOptions.h"
#include "IHandler.h"

namespace bayan {

namespace fs = std::filesystem;
/**
    \brief Class for finding files according to options parameters.
*/

class FileFinder {

public:
    FileFinder(IOptionsSP);

    /**
    \brief Starts a search.
    */
    void scan();

    /**
    \brief Outputs found files matching the conditions to the std::cout.

    */
    void out(IHandlerSP) const;

private:
    bool isMatchMasks(const std::string&) const;

    bool isPathExclude(const fs::recursive_directory_iterator&);

private:
    IOptionsSP requirement;
    std::vector<std::pair<fs::path, size_t>> fileList;
};

} // namespace bayan
