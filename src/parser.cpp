#include <iostream>
#include <exception>
#include "parser.h"
#include "options.h"
#include "crc32hash.h"
#include "md5hash.h"

namespace bayan {


struct BadOption: public std::logic_error {

    explicit BadOption(const std::string &input)
        : std::logic_error(input) {}
};


OptionsParser::OptionsParser() : optDescription("Options") {

    using path = std::filesystem::path;
    namespace bpo = boost::program_options;

    optDescription.add_options()
    (
        "includes,i",
        bpo::value<std::vector<path>>()->default_value(std::vector<path>(1, "./"), "./")->
        multitoken()->zero_tokens()->composing(),
        "Include paths for scanning."
    )
    (
        "excludes,e",
        bpo::value<std::vector<path>>()->default_value(std::vector<path>(), "empty")->
        multitoken()->zero_tokens()->composing(),
        "Exclude paths from scanning."
    )
    (
        "level,l",
        bpo::value<long>()->default_value(0L),
        "Scan nesting level."
    )
    (
        "min-size,s",
        bpo::value<long>()->default_value(1L),
        "Minimum file size in bytes for scanning."
    )
    (
        "masks,m",
        bpo::value<std::vector<std::string>>()->default_value(std::vector<std::string>(), "'*'")->
        multitoken()->zero_tokens()->composing(),
        "Masks for comparison."
    )
    (
        "block-size,b",
        bpo::value<long>()->default_value(512L),
        "Block size for reading file."
    )
    (
        "algorithm,a",
        bpo::value<std::string>()->default_value("crc32"),
        "Hash algorithm: md5 or crc32."
    )
    (
        "help,h", "Show this page."
    );

}


IOptionsSP OptionsParser::getOptions(int argc, char** argv) {

    using path = std::filesystem::path;
    namespace bpo = boost::program_options;

    try {
        bpo::store(bpo::parse_command_line(argc, argv, optDescription), variablesMap);

        bpo::notify(variablesMap);

        std::shared_ptr<Options> options = std::make_shared<Options>();

        if(variablesMap.count("help")) {
            std::cout << optDescription << "\n";
            return options;
        }



        if(variablesMap.count("includes")) {

            options->includePaths = variablesMap["includes"].as<std::vector<path>>();

            for(auto& path : options->includePaths) {
                if(path.is_relative()) {
                    path = std::filesystem::canonical(path);
                }
            }
        }


        if(variablesMap.count("excludes")) {

            options->excludePaths = variablesMap["excludes"].as<std::vector<path>>();

            for(auto& path : options->excludePaths) {
                if(path.is_relative()) {
                    path = std::filesystem::canonical(path);
                }
            }
        }

        if (variablesMap.count("level")) {

            long nLevel = variablesMap["level"].as<long>();

            if (nLevel < 0) {
                throw BadOption("Level scanning must be unsigned integer");
            }

            options->levelScanning = nLevel + 1;
        }

        if (variablesMap.count("min-size")) {

            long nMinSize = variablesMap["min-size"].as<long>();

            if (nMinSize < 1) {
                throw BadOption("Minimum file size must be greater than 0");
            }

            options->minFileSize = static_cast<std::size_t>(nMinSize);
        }

        if (variablesMap.count("masks")) {

            for(auto& mskStr : variablesMap["masks"].as<std::vector<std::string>>())
                options->masks.emplace_back(std::string(mskStr));

        }

        if (variablesMap.count("block-size")) {

            long nBlockSize = variablesMap["block-size"].as<long>();

            if (nBlockSize < 1) {
                throw BadOption("Minimum block size must be greater than 0");
            }

            options->blockSize = static_cast<size_t>(nBlockSize);
        }

        if (variablesMap.count("algorithm")) {

            std::string strHash = variablesMap["algorithm"].as<std::string>();

            if (strHash != "crc32" && strHash != "md5") {
                throw BadOption("The hash algorithm '" + strHash + "' not supported");
            }
            if(strHash == "crc32")
                options->hash = std::make_shared<Crc32Hash>();
            else
                options->hash = std::make_shared<Md5Hash>();
        }

        return options;

    }
    catch(std::exception& e) {

        std::cout << "Error: " << e.what() << std::endl << std::endl;
        std::cout << optDescription << std::endl;
        return std::shared_ptr<Options>();

    }

}


} // namespace bayan
