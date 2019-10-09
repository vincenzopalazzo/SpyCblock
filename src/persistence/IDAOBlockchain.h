// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

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
