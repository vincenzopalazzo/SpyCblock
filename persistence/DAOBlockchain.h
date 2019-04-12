//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//

#ifndef SPYCBLOCK_DAOBLOCKCHAIN_H
#define SPYCBLOCK_DAOBLOCKCHAIN_H

#include<experimental/filesystem>

#include "IDAOBlockchain.h"

using namespace std;
namespace fs = std::experimental::filesystem;

namespace spyCBlock{

    class DAOBlockchain : public IDAOBlockchain{

    private:

        std::vector<spyCBlock::Block>* readBlock(fs::directory_entry entry);

        bool isBlockFileBlk(fs::directory_entry entry);

        bool isBlockGenesi(fs::directory_entry entry, spyCBlock::Block* genericBlock);

    public:
        virtual ~DAOBlockchain();

        DAOBlockchain();

        vector<Block> loadBlocks(string path) override;

        bool saveBlock(string inputPath, string outputPath) override;

    };

}


#endif //SPYCBLOCK_DAOBLOCKCHAIN_H
