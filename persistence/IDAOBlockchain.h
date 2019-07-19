//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//

#ifndef SPYCBLOCK_IDAOBLOCKCHAIN_H
#define SPYCBLOCK_IDAOBLOCKCHAIN_H

#include <vector>

#include "../structure/block/block.h"

using namespace std;

namespace spyCBlock
{

    class IDAOBlockchain
    {

      public:
          virtual vector<unique_ptr<Block>> loadBlocks(string &path) = 0;

          virtual bool saveBlock(string inputPath, string outputPath) = 0;

    };
}

#endif //SPYCBLOCK_IDAOBLOCKCHAIN_H
