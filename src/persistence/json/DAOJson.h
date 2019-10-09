// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

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

      bool saveBlock(string inputPath, string outputPath, int &height) override;

  };

}
#endif // DAOJSON_H
