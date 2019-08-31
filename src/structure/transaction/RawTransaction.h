#ifndef PARSINGBLOCKCHAIN_RAWTRANSACTION_H
#define PARSINGBLOCKCHAIN_RAWTRANSACTION_H

#include <vector>

#include <glog/logging.h>
#include "../../../include/spycblockrpc/core/graph/WrapperInformations.h"
#include "../../../src/util/serialize.h"

#include "TransactionOutput.h"
#include "TransactionInput.h"
#include "TransactionWitness.h"

// @author https://github.com/vincenzopalazzo
namespace spyCBlock{

    class RawTransaction{

      public:

          enum class Type{PRIMITIVE = 1, WITNESS = 2};

          int32_t getVersion() const;

          uint8_t getFlag() const;

          uint8_t getMarker() const;

          const DVarInt& getNumberTxIn() const;

          const std::vector<TransactionInput> &getTxIn() const;

          const DVarInt& getNumberTxOut() const;

          const std::vector<TransactionOutput> &getTxOut() const;

          std::string getHashRawTransaction() const;

          uint32_t getLockTime() const;

          std::string toString();

          void decode(std::ifstream &stream);

          std::string toSerealizationForm() const;

          void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson);

          void toGraphForm(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

          void toTransactionsGraph(std::ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper);

    private:

          Type type;

          int32_t version;

          uint8_t marker;

          uint8_t flag;

          DVarInt numberTxIn;

          std::vector<TransactionInput> txIn; // TODO che cosa cambia nella transazione coind base?

          DVarInt numberTxOut;

          std::vector<TransactionOutput> txOut;

          uint32_t lockTime;

          std::string hashRawTransaction;

          std::vector<TransactionWitness> txsWitness;

    };
}
#endif //PARSINGBLOCKCHAIN_RAWTRANSACTION_H
