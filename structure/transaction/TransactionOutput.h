#ifndef PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H
#define PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H

#include <cstdint>

#include <nlohmann/json.hpp>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../../include/spycblockrpc/core/graph/WrapperInformations.h"

#include "../type/DScript.h"

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */
namespace spyCBlock{

    class TransactionOutput
    {
      private:

          int64_t nValue;

          DScript script;
          //Addintiona information
          std::string hashOutputTransaction;

      public:

          const int64_t& getNValue() const;

          const DScript& getScript() const;

          const std::string& getHashOutputTransaction() const;

          std::string toString();

          void decode(std::ifstream &stream);

          std::string toSerealizationForm() const;

          bool isScriptNull();

          //TODO can be removed
          nlohmann::json toJson();

          void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

          void toGraphForm(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);
    };
}
#endif //PARSINGBLOCKCHAIN_TRANSACTIONOUTPUT_H


