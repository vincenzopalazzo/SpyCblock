// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H
#define PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <zlib.h>

#include <cstdint>

#include "../../../include/spycblockrpc/src/core/graph/WrapperInformations.h"
#include "../type/DScript.h"
#include "../type/Outpoint.h"

namespace spyCBlock {
class TransactionInput {
 public:
  const DScript &getScript() const;

  uint32_t getSequences() const;

  const OutPoint &getOutpoint() const;

  void setOutpoint(const OutPoint &outpoint);

  const std::string &getHashInputTransaction() const;

  std::string toString();

  void decode(std::ifstream &stream);

  std::string toSerealizationForm() const;

  bool isScriptNull();

  void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

  void toGraphForm(std::ofstream &outputStream,
                   spyCBlockRPC::WrapperInformations &wrapper);

  void toTransactionsGraph(std::ofstream &outputStream,
                           spyCBlockRPC::WrapperInformations &wrapper);

  void toCompressedTransactionsGraph(
      gzFile &file, spyCBlockRPC::WrapperInformations &wrapper);

 private:
  OutPoint outpoint;

  DScript script;

  uint32_t sequences;

  std::string hashInputTransaction;
};
}  // namespace spyCBlock

#endif  // PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H
