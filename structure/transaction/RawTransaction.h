#ifndef PARSINGBLOCKCHAIN_RAWTRANSACTION_H
#define PARSINGBLOCKCHAIN_RAWTRANSACTION_H

#include <vector>

#include <glog/logging.h>
#include <nlohmann/json.hpp>

#include "TransactionOutput.h"
#include "TransactionInput.h"
#include "../../util/serialize.h"

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */
namespace spyCBlock{

    class RawTransaction{

      private:

          int32_t version;
          DVarInt numberTxIn;
          std::vector<TransactionInput> txIn; // TODO che cosa cambia nella transazione coind base?
          DVarInt numberTxOut;
          std::vector<TransactionOutput> txOut;
          uint32_t lockTime;

          //Additiona information
          std::string hashRawTransaction;

      public:

          int32_t getVersion() const;

          const DVarInt& getNumberTxIn() const;

          const std::vector<TransactionInput> &getTxIn() const;

          const DVarInt& getNumberTxOut() const;

          const std::vector<TransactionOutput> &getTxOut() const;

          std::string getHashRawTransaction() const;

          uint32_t getLockTime() const;

          std::string toString();

          void decode(std::ifstream &stream);

          std::string toSerealizationForm() const;

          nlohmann::json toJson();

          void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

    };
}
#endif //PARSINGBLOCKCHAIN_RAWTRANSACTION_H
