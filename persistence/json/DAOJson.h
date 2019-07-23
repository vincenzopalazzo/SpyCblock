#ifndef DAOJSON_H
#define DAOJSON_H

#include <memory>

#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include "../IDAOBlockchain.h"
#include "../../structure/block/block.h"

namespace spyCBlock {

  class DAOJson : public IDAOBlockchain
  {
    public:
      vector<unique_ptr<Block>> loadBlocks(string &path) override;

      bool saveBlock(string inputPath, string outputPath) override;

    private:
      void convertToJson(vector<Block> &blocks, ofstream &outputPath);

      void convertToJsonRapidJson(vector<Block> &blocks, ofstream &outputPath);

  };

}
#endif // DAOJSON_H
