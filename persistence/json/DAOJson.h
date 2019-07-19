#ifndef DAOJSON_H
#define DAOJSON_H

#include <memory>

#include "../IDAOBlockchain.h"
#include "../../structure/block/block.h"

namespace spyCBlock {

  class DAOJson : public IDAOBlockchain
  {
    public:
      vector<unique_ptr<Block>> loadBlocks(string &path) override;

      bool saveBlock(string inputPath, string outputPath) override;

    private:
      void convertToJson(vector<unique_ptr<Block>> &blocks, string outputPath);
  };

}
#endif // DAOJSON_H
