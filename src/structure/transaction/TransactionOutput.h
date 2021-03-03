// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H
#define PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#include <cstdint>

#include "../../../include/spycblockrpc/src/core/graph/WrapperInformations.h"
#include "../type/DScript.h"

namespace spyCBlock {
class TransactionOutput {
 public:
  const int64_t& getNValue() const;

  const DScript& getScript() const;

  const std::string& getHashOutputTransaction() const;

  std::string toString();

  void decode(std::ifstream& stream);

  std::string toSerealizationForm() const;

  bool isScriptNull();

  void toJson(rapidjson::Writer<rapidjson::OStreamWrapper>& writerJson);

  void toGraphForm(std::ofstream& outputStream,
                   spyCBlockRPC::WrapperInformations& wrapper);

  void toTransactionsGraph(std::ofstream& outputStream,
                           spyCBlockRPC::WrapperInformations& wrapper);

 private:
  int64_t nValue;

  DScript script;

  std::string hashOutputTransaction;
};
}  // namespace spyCBlock
#endif  // PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H
