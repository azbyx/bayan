#pragma once

#include <vector>
#include "IHash.h"
#include "parser.h"

namespace bayan {



/**
    \brief A class for working with the received command line options.
*    Required for the Finder and Handler class.
*/
class Options : public IOptions {

    friend OptionsParser;

public:
    void printOpt() override;

    std::string getHashOfBuffer(const char*) override;

    size_t getBlockSize() const override;

    size_t getMinFileSize() const override;

    long getLevelScanning() const override;

    std::vector<Mask> getMasks() const override;

    std::vector<path> getIncludePaths() const override;

    std::vector<path> getExcludePaths() const override;

private:

    std::vector<path> includePaths;
    std::vector<path> excludePaths;
    long              levelScanning;
    std::size_t       minFileSize;
    std::vector<Mask> masks;
    std::size_t       blockSize;
    IHashSP           hash;

};

} // namespace bayan

