#include "LevelData.h"

std::unordered_map<char, std::string> tileToEntity = {
    { '1', "1HBrick" },
    { '2', "2HBrick" },
    { '3', "3HBrick" },
};

std::vector<std::vector<std::string>> levels = {
    {
        "               ",
        "    1111111    ",
    },
    {
        "               ",
        "   111111111   ",
        "   122222221   ",
        "   111111111   ",
        "               ",
    },
    {
        "               ",
        "112111111111211",
        "112333333333211",
        "112222222222211",
        "               ",
    },
};
