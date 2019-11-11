// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef DAOJSON_H
#define DAOJSON_H

#include <memory>

#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include "../IDAOBlockchain.h"

namespace spyCBlock {

  class DAOJson : public IDAOBlockchain
  {
    public:

      bool saveBlock(const std::string &inputPath, const std::string &outputPath, int &height) override;

      //not implemented for the moment
      virtual bool saveBlockCompress(const string &inputPath, const string &outputPath, int &height);
  };

}
#endif // DAOJSON_H
