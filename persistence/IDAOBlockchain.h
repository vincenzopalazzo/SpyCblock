//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//

#ifndef SPYCBLOCK_IDAOBLOCKCHAIN_H
#define SPYCBLOCK_IDAOBLOCKCHAIN_H

#include <vector>

#include "../structure/block/block.h"

namespace spyCBlock
{

    class IDAOBlockchain
    {

      public:

          virtual bool saveBlock(std::string inputPath, std::string outputPath, int &height) = 0;

    };
}

#endif //SPYCBLOCK_IDAOBLOCKCHAIN_H
