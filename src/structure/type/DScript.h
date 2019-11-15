// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef PARSINGBLOCKCHAIN_CSCRIPT_H
#define PARSINGBLOCKCHAIN_CSCRIPT_H

#include <vector>
#include <fstream>

#include "DVarInt.h"

namespace spyCBlock
{
    class DScript
    {
      public:

          const std::string &getRawScriptString() const;

          const DVarInt &getScriptLenght() const;

          std::string getScriptToSerializationForm() const;

          std::string toString();

          const std::string &getScriptString() const;

          void decode(std::ifstream &stream);

      private:

        DVarInt scriptLenght;

        std::string scriptString;

        std::string rawScriptString;
      };
}


#endif //PARSINGBLOCKCHAIN_CSCRIPT_H
