//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//


#ifndef PARSINGBLOCKCHAIN_RAWTRANSACTION_H
#define PARSINGBLOCKCHAIN_RAWTRANSACTION_H

#include <vector>

#include <glog/logging.h>
#include <nlohmann/json.hpp>

#include "TransactionOutput.h"
#include "TransactionInput.h"
#include "../../util/serialize.h"

using namespace std;
using namespace nlohmann;

namespace spyCBlock{

    class RawTransaction{

    private:

        int32_t version;
        DVarInt numberTxIn;
        vector<unique_ptr<TransactionInput>> txInd; // TODO che cosa cambia nella transazione coind base?
        DVarInt numberTxOut;
        vector<unique_ptr<TransactionOutput>> txOut;
        uint32_t lockTime;

        //Additiona information
        string hashRawTransaction;

    public:

        virtual ~RawTransaction();

        int32_t getVersion() const;

        const DVarInt& getNumberTxIn() const;

        const vector<unique_ptr<TransactionInput>>& getTxInd() const;

        const DVarInt& getNumberTxOut() const;

        const vector<unique_ptr<TransactionOutput>>& getTxOut() const;

        string getHashRawTransaction() const;

        uint32_t getLockTime() const;

        string toString();

        void decode(std::ifstream &stream);

        string toSerealizationForm();

        json toJson();

    };
}
#endif //PARSINGBLOCKCHAIN_RAWTRANSACTION_H
