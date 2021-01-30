#include <iostream>
#include "finder.h"

namespace bayan {

FileFinder::FileFinder(IOptionsSP inParam) {

    if(inParam)
        requirement = inParam;
    else
        throw std::runtime_error("Invalid options.");

}

void FileFinder::scan() {

    for(const auto& curIncludePath : requirement->getIncludePaths()) {

        auto curIter = fs::recursive_directory_iterator(curIncludePath);
        auto endIter = fs::recursive_directory_iterator();

        for(; curIter != endIter; ++curIter) {

            if(
                curIter.depth() < requirement->getLevelScanning() &&
                !isPathExclude(curIter) &&
                curIter->is_regular_file() &&
                curIter->file_size() > requirement->getMinFileSize() &&
                isMatchMasks(curIter->path().filename().string())
               )
            {
                    fileList.emplace_back(curIter->path(), curIter->file_size());

            }
        }
    }
}


bool FileFinder::isPathExclude(const fs::recursive_directory_iterator& inIter) {

    bool res = false;

    for(const auto& msk : requirement->getExcludePaths()) {
        if(inIter->path().parent_path() == msk) {
            res = true;
            break;
        }
    }

    return res;

}


void FileFinder::out(IHandlerSP hendl) const {

     if(hendl) {
        for(const auto& i : fileList)
                hendl->addFile(i.first, i.second);
    }

}


bool FileFinder::isMatchMasks(const std::string& inStr) const {

    auto masks = requirement->getMasks();

    bool res = !masks.size();

    for(Mask mask : masks) {
        if(mask(inStr)) {
            res = true;
            break;
        }
    }

    return res;

}


} // namespace bayan
