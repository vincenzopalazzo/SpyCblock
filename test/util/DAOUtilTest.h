// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef DAOUTILTEST_H
#define DAOUTILTEST_H

#include <experimental/filesystem>
#include <vector>

#include "../../src/structure/block/Block.h"

namespace spyCBlock {
class DAOUtilTest {
 public:
  std::vector<Block> loadBlocks(std::string pathinput);

 private:
  std::vector<Block> readBlocks(
      std::experimental::filesystem::directory_entry entry);

  bool isBlockFileBlk(std::experimental::filesystem::directory_entry &entry);
};
}  // namespace spyCBlock

#endif  // DAOUTILTEST_H
