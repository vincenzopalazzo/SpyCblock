// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef DAOJSON_H
#define DAOJSON_H

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#include <memory>

#include "../IDAOBlockchain.h"

namespace spyCBlock {

class DAOJson : public IDAOBlockchain {
 public:
  bool saveBlock(const std::string &inputPath,
                 const std::string &outputPath) override;

  // not implemented for the moment
  virtual bool saveBlockCompress(const string &inputPath,
                                 const string &outputPath);
};

}  // namespace spyCBlock
#endif  // DAOJSON_H
