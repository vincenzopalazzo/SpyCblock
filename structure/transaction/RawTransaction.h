//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//


#ifndef PARSINGBLOCKCHAIN_RAWTRANSACTION_H
#define PARSINGBLOCKCHAIN_RAWTRANSACTION_H

#include <vector>
#include "TransactionOutput.h"
#include "TransactionInput.h"
#include <glog/logging.h>

using namespace std;

class RawTransaction{
/*TODO left a number o txOut and txInf*/
private:
    uint32_t version;
    DVarInt numberTxIn;
    std::vector<TransactionInput> txInd; // che cosa cambia nella transazione coind base?
    DVarInt numberTxOut;
    std::vector<TransactionOutput> txOut;
    uint32_t lockTime;

public:

    virtual ~RawTransaction();

    uint32_t getVersion() const;

    const DVarInt &getNumberTxIn() const;

    const vector<TransactionInput> &getTxInd() const;

    const DVarInt &getNumberTxOut() const;

    const vector<TransactionOutput> &getTxOut() const;

    uint32_t getLockTime() const;

    string toString();

    void decode(std::ifstream &stream);
};

#endif //PARSINGBLOCKCHAIN_RAWTRANSACTION_H