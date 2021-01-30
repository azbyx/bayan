#pragma once

#include <string>
#include <regex>
#include <boost/algorithm/string/replace.hpp>

namespace bayan {

/**
    \brief Class for checking the file name against the mask..
*/
class Mask {

public:
    Mask(std::string inStr) {

        boost::replace_all(inStr, ".", "\\.");
        boost::replace_all(inStr, "*", "\\*");
        boost::replace_all(inStr, "?", "\\?");
        boost::replace_all(inStr, "\\?", ".");
        boost::replace_all(inStr, "\\*", ".*");

        regexpr = std::regex(inStr, std::regex::icase);

    }

    bool operator() (const std::string& strValue) {
        return std::regex_match(strValue, match, regexpr);
    }

private:
    std::regex regexpr;
    std::smatch match;
};



} // namespace bayan
