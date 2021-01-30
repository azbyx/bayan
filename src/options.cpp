#include <iostream>
#include <exception>
#include "options.h"
#include "crc32hash.h"
#include "md5hash.h"

namespace bayan {



void Options::printOpt() {

    for(const auto& i : includePaths)
        std::cout << "Ipath: " << i << std::endl;
    for(const auto& i : excludePaths)
        std::cout << "Epath: " << i << std::endl;
    std::cout << masks.size() << std::endl;
    std::cout << levelScanning << std::endl;
    std::cout << minFileSize << std::endl;
    std::cout << blockSize << std::endl;
    std::cout << hash->hashAsString("0", 3) << std::endl;
}



std::string Options::getHashOfBuffer(const char* inBuffer) {
    return hash->hashAsString(inBuffer, blockSize);
}


size_t Options::getBlockSize() const { return blockSize; }

size_t Options::getMinFileSize() const { return minFileSize; }

long Options::getLevelScanning() const { return levelScanning; }

std::vector<Mask> Options::getMasks() const { return masks; }

std::vector<Options::path> Options::getIncludePaths() const { return includePaths; }

std::vector<Options::path> Options::getExcludePaths() const { return excludePaths; }


} // namespace bayan
