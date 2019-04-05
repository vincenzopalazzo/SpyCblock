//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//


#ifndef PARSINGBLOCKCHAIN_RAWTRANSACTION_H
#define PARSINGBLOCKCHAIN_RAWTRANSACTION_H

#include <vector>
#include "TransactionOutput.h"
#include "TransactionInput.h"
#include <glog/logging.h>
#include "../../util/serialize.h"

using namespace std;

namespace spyCBlock{

    class RawTransaction{

    private:
        int32_t version;
        DVarInt numberTxIn;
        vector<TransactionInput> txInd; // TODO che cosa cambia nella transazione coind base?
        DVarInt numberTxOut;
        vector<TransactionOutput> txOut;
        uint32_t lockTime;

    public:


        virtual ~RawTransaction();

        int32_t getVersion() const;

        const DVarInt & getNumberTxIn() const;

        const vector<TransactionInput> &getTxInd() const;

        const DVarInt & getNumberTxOut() const;

        const vector<TransactionOutput> &getTxOut() const;

        uint32_t getLockTime() const;

        string toString();

        void decode(std::ifstream &stream);
    };
}
#endif //PARSINGBLOCKCHAIN_RAWTRANSACTION_H
