#ifndef PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H
#define PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H

#include <cstdint>

#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../../include/spycblockrpc/core/graph/WrapperInformations.h"

#include "../type/DScript.h"

//@author https://github.com/vincenzopalazzo
namespace spyCBlock
{
    class TransactionOutput
    {
      public:

          const int64_t& getNValue() const;

          const DScript& getScript() const;

          const std::string& getHashOutputTransaction() const;

          std::string toString();

          void decode(std::ifstream &stream);

          std::string toSerealizationForm() const;

          bool isScriptNull();

          void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

          void toGraphForm(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

          void toTransactionsGraph(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

      private:

          int64_t nValue;

          DScript script;

          std::string hashOutputTransaction;
    };
}
#endif //PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H


