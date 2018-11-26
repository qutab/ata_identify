#include "CommandLineParser.hpp"

#include <iostream>

namespace utils {

namespace {
const auto usageMsg = R"EOF(
usage: ata filename [--verbose] [-v]

ata parses SATA disk’s response for ATA IDENTIFY.
It reports:
  1) Disk's model number
  2) Highest supported Ultra DMA mode
  3) Whether SMART self test is supported
)EOF";

enum
{
    PROGNAME_INDEX = 0,
    FILENAME_INDEX = 1,
    VERBOSITY_INDEX = 2

};
} /* anonymous namespace */

CommandLineParser::CommandLineParser(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
    {
        argsM.emplace_back(argv[i]);
    }
}

CommandLineParser::~CommandLineParser() = default;

std::string CommandLineParser::getFilename() const
{
    try
    {
        return std::string{argsM.at(FILENAME_INDEX)};
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << usageMsg << std::endl;
    }
    catch (...)
    {
        // pass
    }
    std::exit(EXIT_FAILURE);

    // avoid compiler warning, program will terminate anyway
    return std::string{};
}

bool CommandLineParser::isVerbose() const
{
    try
    {
        const auto& str = argsM.at(VERBOSITY_INDEX);
        return (str.compare("--verbose") == 0) or (str.compare("-v") == 0);
    }
    catch (const std::exception& e)
    {
        return false;
    }
    catch (...)
    {
        // pass
    }
    std::exit(EXIT_FAILURE);
    return false;
}

std::string CommandLineParser::getUsageMsg() const
{
    return usageMsg;
}

} /* namespace utils */
