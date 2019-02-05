//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#include <vector>
#include "TransactionOutput.cpp"
#include "TransactionInput.cpp"

#ifndef PARSINGBLOCKCHAIN_RAWTRANSACTION_H
#define PARSINGBLOCKCHAIN_RAWTRANSACTION_H
#endif //PARSINGBLOCKCHAIN_RAWTRANSACTION_H



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
    const DVarInt &getNumberTxIn() const;

    const DVarInt &getNumberTxOut() const;

    uint32_t getVersion() const;

    const std::vector<TransactionInput> &getTxInd() const;


    const std::vector<TransactionOutput> &getTxOut() const;

    uint32_t getLockTime() const;

    void decode(std::ifstream &stream);
};