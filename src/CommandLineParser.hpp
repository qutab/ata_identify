#pragma once

#include <string>
#include <vector>

namespace utils {

/** Parser for command line arguments */
class CommandLineParser final
{
public:
    /**
     * @param argc number of command line args
     * @param argv array of command line args
     */
    CommandLineParser(int argc, char* argv[]);
    ~CommandLineParser();

    /** @return upstream endpoint parsed from command line */
    std::string getFilename() const;

    /** @return whether verbose logging is requested */
    bool isVerbose() const;

    std::string getUsageMsg() const;

private:
    std::vector<std::string> argsM;
};

} /* namespace utils */
