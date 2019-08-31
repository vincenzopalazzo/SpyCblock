#ifndef DAOUTILTEST_H
#define DAOUTILTEST_H

#include <vector>
#include<experimental/filesystem>

#include "../../structure/block/block.h"

namespace spyCBlock
{
    class DAOUtilTest
    {
        public:

            std::vector<Block> loadBlocks(std::string pathinput);

        private:

            std::vector<Block> readBlocks(std::experimental::filesystem::directory_entry entry);

            bool isBlockFileBlk(std::experimental::filesystem::directory_entry &entry);

    };
}

#endif // DAOUTILTEST_H
