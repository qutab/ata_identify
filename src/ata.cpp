#include "CommandLineParser.hpp"
#include "DeserializeUtils.hpp"
#include "Field.hpp"
#include "LogUtils.hpp"
#include "ParseUtils.hpp"
#include "PlatformDefs.hpp"

namespace {

enum
{
    MODEL_NAME_MIN = 27,
    MODEL_NAME_MAX = 46,
    DMA_MODE_WORD = 88,
    SELF_TEST_84_WORD = 84,
    SELF_TEST_87_WORD = 87,
};

} //anonymous namespace

int main(int argc, char* argv[])
{
    utils::CommandLineParser parser{argc, argv};
    std::ifstream ifstream(parser.getFilename());
    if (ifstream.fail())
    {
        std::cerr << "Bad command or file name." << std::endl;
        std::cout << parser.getUsageMsg() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    const bool isVerbose = parser.isVerbose();

    ata::Field modelName(MODEL_NAME_MIN, MODEL_NAME_MAX);
    ata::Field dmaMode(DMA_MODE_WORD);
    ata::Field selfTest84(SELF_TEST_84_WORD);
    ata::Field selfTest87(SELF_TEST_87_WORD);

    // Buffer
    std::vector<char> buffer;

    // Sanity check - Word 47's MSB is 0x80
    deserialize::readBytes(ifstream, ata::Field{47}, buffer);
    assert(buffer.at(0) == static_cast<char>(0x80));

    // model name
    deserialize::readBytes(ifstream, modelName, buffer);
    log::printBuffer("Model name: ", buffer);

    // DMA mode
    deserialize::readBytes(ifstream, dmaMode, buffer);
    if (isVerbose)
    {
        log::printBinary("DMA Mode: ", buffer);
    }
    ata::parseUltraDmaModeSupport(buffer.at(defs::LSB_IDX));

    // Self test support
    deserialize::readBytes(ifstream, selfTest84, buffer);
    char st84 = buffer.at(defs::LSB_IDX);
    if (isVerbose)
    {
        log::printBinary("Self Test - 84", buffer);
    }

    deserialize::readBytes(ifstream, selfTest87, buffer);
    char st87 = buffer.at(defs::LSB_IDX);
    if (isVerbose)
    {
        log::printBinary("Self Test - 87", buffer);
    }

    ata::parseSmartStSupport(st84, st87);

	return EXIT_SUCCESS;
}
