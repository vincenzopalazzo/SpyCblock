// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H
#define PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

#include <cstdint>

#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../type/Outpoint.h"
#include "../../../include/spycblockrpc/src/core/graph/WrapperInformations.h"

#include "../type/DScript.h"

namespace spyCBlock
{
    class TransactionInput
    {
      public:

          const DScript& getScript() const;

          uint32_t getSequences() const;

          const OutPoint& getOutpoint() const;

          void setOutpoint(const OutPoint &outpoint);

          const std::string& getHashInputTransaction() const;

          std::string toString();

          void decode(std::ifstream &stream);

          std::string toSerealizationForm();

          bool isScriptNull();

          void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

          void toGraphForm(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

          void toTransactionsGraph(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

      private:

          OutPoint outpoint;

          DScript script;

          uint32_t sequences;

          std::string hashInputTransaction;
    };
}

#endif //PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H
