#include "LevelData.h"

std::unordered_map<char, int> tileToHp = {
    { '1', 1 },
    { '2', 2 },
    { '3', 3 },
};

// Max 14 rows per level make sense. Otherwise the bricks are below the paddle.

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
