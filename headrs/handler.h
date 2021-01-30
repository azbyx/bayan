#pragma once

#include <vector>
#include <fstream>
#include "IHandler.h"
#include "IOptions.h"

namespace bayan {

/**
    \brief Class for storing file details.
    [path] - file path;
    [readerStream] - the stream associated with the file to read it.
    [hashesOfBlocks] - array for keeping hashes of blocks.
    [fileSize] - size of file.
*/

struct File {
    fs::path path;
    std::unique_ptr<std::ifstream> readerStream;
    std::vector<std::string> hashesOfBlocks;
    size_t fileSize;
};



/**
    \brief Class for reading and comparing files.
*/

class Handler : public IHandler {

public:
    Handler(IOptionsSP);

    void addFile(const fs::path&, size_t) override;

private:
    void searchEquals();

    std::string readBlock(File&);

    std::string readNextBlock(File&, size_t);

private:
    IOptionsSP options;
    size_t blockSize;
    std::unique_ptr<char[]> buffer;
    std::vector<File> fileList;

};

} // namespace bayan
