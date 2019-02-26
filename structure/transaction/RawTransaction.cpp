//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <cstdint>
#include <sstream>

#include "RawTransaction.h"

using namespace spyCBlock;

void RawTransaction::decode(std::ifstream &stream) {
    Unserialize(stream, version);
    LOG(INFO) << "Version raw transaction " << version;
    this->numberTxIn.decode(stream);
    LOG(INFO) << "Numbar transaction input in raw transaction " << numberTxIn.getValue();
    txInd.clear();
    for(int i = 0; i < this->numberTxIn.getValue(); i++)
    {
        TransactionInput *transaction = new TransactionInput();
        transaction->decode(stream);
        this->txInd.push_back(*transaction);
        delete transaction;
    }
    this->numberTxOut.decode(stream);
    LOG(INFO) << "Numbar transaction output in raw transaction " << numberTxOut.getValue();
    txOut.clear();
    for(int i = 0; i < numberTxOut.getValue(); i++)
    {
        TransactionOutput *transactionOutput = new TransactionOutput();
        transactionOutput->decode(stream);
        this->txOut.push_back(*transactionOutput);
        delete transactionOutput;
    }
    Unserialize(stream, this->lockTime);
}

string RawTransaction::toString() {
    stringstream *stream = new stringstream();
    *stream << "---------- Raw Transaction ----------" << endl;
    *stream << "Version: " << version << endl;
    *stream << "---------- Transaction Input ----------"<< endl;
    *stream << "Number Transaction In: " << numberTxIn.getValue() << endl;
    for(int i = 0; i < numberTxIn.getValue(); i++)
    {
        *stream << this->txInd.at(i).toString();
    }
    *stream << "---------- Transaction Output ----------"<< endl;
    *stream << "Number Transaction out: " << numberTxOut.getValue() << endl;
    for(int i = 0; i < numberTxOut.getValue(); i++)
    {
        *stream << this->txOut.at(i).toString();
    }
    *stream << this->lockTime;
    string result = stream->str();
    delete stream;
    return result;
}

uint32_t RawTransaction::getVersion() const {
    return version;
}

const DVarInt &RawTransaction::getNumberTxIn() const {
    return numberTxIn;
}

const vector<TransactionInput> &RawTransaction::getTxInd() const {
    return txInd;
}

const DVarInt &RawTransaction::getNumberTxOut() const {
    return numberTxOut;
}

const vector<TransactionOutput> &RawTransaction::getTxOut() const {
    return txOut;
}

uint32_t RawTransaction::getLockTime() const {
    return lockTime;
}

RawTransaction::~RawTransaction() {
}


