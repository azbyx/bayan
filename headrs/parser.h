#pragma once

#include <boost/program_options.hpp>
#include "IOptions.h"

namespace bayan {


/**
    \brief Class for parse command line options and store their in the Options object.
*/
class OptionsParser {

public:
    OptionsParser();

    IOptionsSP getOptions(int, char**);

private:
    boost::program_options::options_description optDescription;
    boost::program_options::variables_map variablesMap;

};

} // namespace bayan
