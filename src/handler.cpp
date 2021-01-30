#include <iostream>
#include <cstring>
#include "handler.h"


namespace bayan {


Handler::Handler(IOptionsSP inOpts) : options(inOpts) {

    if(options) {
        blockSize = options->getBlockSize();
        buffer = std::make_unique<char[]>(blockSize);
    }
    else
        throw std::runtime_error("Invalid options.");

}


void Handler::addFile(const fs::path& curPath, size_t fileSize) {

    fileList.emplace_back(File{curPath,
                          std::unique_ptr<std::ifstream>(),
                          std::vector<std::string>(),
                          fileSize});
    if(fileList.size() > 1)
        searchEquals();

}

std::string Handler::readBlock(File& curFile) {

    auto& curStream = curFile.readerStream;

    if(!curStream) {
        curStream = std::make_unique<std::ifstream>(curFile.path, std::ios::binary);
    }

    size_t curBlock = curFile.hashesOfBlocks.size();
    size_t curPos = curBlock * blockSize;

    curStream->seekg(curPos, std::ios_base::beg);
    curStream->read(buffer.get(), blockSize);

    if(curStream->eof()) {
        size_t noUsedRemainder = curFile.fileSize - curPos;
        std::memset(buffer.get() + noUsedRemainder, 0, blockSize - noUsedRemainder);
    }

/*
    std::cout << "blockSize __________________________________________________" << blockSize << std::endl;
    for(size_t i = 0; i < blockSize; ++i)
        std::cout << buffer[i];
    std::cout<< std::endl;
*/
    std::string res = options->getHashOfBuffer(buffer.get());
    curFile.hashesOfBlocks.push_back(res);

    return res;

}

std::string Handler::readNextBlock(File& curFile, size_t blockIndex) {

    if(curFile.hashesOfBlocks.size() > blockIndex)
        return curFile.hashesOfBlocks.at(blockIndex);
    else
        return readBlock(curFile);

}


void Handler::searchEquals() {

    auto curIter = fileList.rbegin();

    auto nextBlockExist = [this](auto& it) {
        return it->hashesOfBlocks.size() * blockSize < it->fileSize;
    };

    for(auto nextIter = std::next(curIter); nextIter != fileList.rend(); ++nextIter) {

        if(curIter->fileSize == nextIter->fileSize){

            for(size_t i = 0; curIter->fileSize / blockSize > i; ++i) {
                if(nextBlockExist(curIter) && readNextBlock(*curIter, i) != readNextBlock(*nextIter, i))
                    break;
            }

            if(curIter->hashesOfBlocks.size() &&
               curIter->hashesOfBlocks.size() == nextIter->hashesOfBlocks.size() &&
               curIter->hashesOfBlocks.back() == nextIter->hashesOfBlocks.back()) {

                std::cout << curIter->path.string() << "\n" << nextIter->path.string() << "\n\n";
            }

        }

    }

}


} // namespace bayan

