// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef PARSINGBLOCKCHAIN_CVARINT_H
#define PARSINGBLOCKCHAIN_CVARINT_H

#include <fstream>

#include "../../util/serialize.h"

namespace spyCBlock
{
  class DVarInt
  {
    public:

        uint64_t getValue() const;

        void decode(std::ifstream &stream);


    private:

      uint64_t value;
  };
}

#endif //PARSINGBLOCKCHAIN_CVARINT_H
