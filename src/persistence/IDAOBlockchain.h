// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SPYCBLOCK_IDAOBLOCKCHAIN_H
#define SPYCBLOCK_IDAOBLOCKCHAIN_H

#include <vector>

#include "../structure/block/Block.h"

namespace spyCBlock {

class IDAOBlockchain {
 public:
  virtual bool saveBlock(const std::string &inputPath,
                         const std::string &outputPath) = 0;

  virtual bool saveBlockCompress(const std::string &inputPath,
                                 const std::string &outputPath) = 0;
};
}  // namespace spyCBlock

#endif  // SPYCBLOCK_IDAOBLOCKCHAIN_H
