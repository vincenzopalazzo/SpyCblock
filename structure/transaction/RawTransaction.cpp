//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <cstdint>

#include "RawTransaction.h"

void RawTransaction::decode(std::ifstream &stream) {
    Unserialize(stream, version);
    this->numberTxIn.decode(stream);
    for(int i = 0; i < this->numberTxIn.getValue(); i++)
    {
        TransactionInput transaction = TransactionInput();
        transaction.decode(stream);
        this->txInd.push_back(transaction);
    }
    this->numberTxOut.decode(stream);
    for(int i = 0; i < numberTxOut.getValue(); i++)
    {
        TransactionOutput transactionOutput = TransactionOutput();
        transactionOutput.decode(stream);
        this->txOut.push_back(transactionOutput);
    }
    Unserialize(stream, this->lockTime);
}

uint32_t RawTransaction::getVersion() const {
    return version;
}


const std::vector<TransactionInput> &RawTransaction::getTxInd() const {
    return txInd;
}

const std::vector<TransactionOutput> &RawTransaction::getTxOut() const {
    return txOut;
}

uint32_t RawTransaction::getLockTime() const {
    return lockTime;
}

const DVarInt &RawTransaction::getNumberTxIn() const {
    return numberTxIn;
}

const DVarInt &RawTransaction::getNumberTxOut() const {
    return numberTxOut;
}
