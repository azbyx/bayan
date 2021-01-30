#define BOOST_TEST_MODULE bulk_test

#include <boost/test/unit_test.hpp>
#include "parser.h"


using namespace bayan;

BOOST_AUTO_TEST_CASE(options) {

    BOOST_REQUIRE(0 == 0);


}

BOOST_AUTO_TEST_CASE(default_options) {

    std::string optStr{"name"};
    char* commands[1]{optStr.data()};
    int numberOfArgs = 1;

    auto options = OptionsParser().getOptions(numberOfArgs, commands);

    BOOST_REQUIRE(options);

    BOOST_REQUIRE(options->getBlockSize() == 512L);

    BOOST_REQUIRE(options->getMinFileSize() == 1);

    BOOST_REQUIRE(options->getLevelScanning() == 1);

    BOOST_REQUIRE(options->getMasks().size() == 0);

    BOOST_REQUIRE(options->getIncludePaths().size() == 1);

    BOOST_REQUIRE(options->getExcludePaths().size() == 0);



}



