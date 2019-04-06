//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <iostream>
#include <regex>
#include "block.h"

using namespace spyCBlock;

Block::~Block()
{
}

void Block::decode(std::ifstream &stream) {
    Unserialize(stream, this->magicNum);
    LOG(INFO) << "Magic numbar readed: " << magicNum;
    Unserialize(stream, this->blocksize);
    LOG(INFO) << "Block sire readed: " << blocksize;
    blockHeader.unserialize(stream);
    this->numbarRawTransaction.decode(stream);
    if (numbarRawTransaction.getValue() == -1) {
        LOG_IF(FATAL, (numbarRawTransaction.getValue() == -1)) << "Error numbarRaw Transaction = " << numbarRawTransaction.getValue();
        //TODO segnalare errore lanciando un eccezione
        return;
    }
    rawTransactions.clear();
    for (int i = 0; i < numbarRawTransaction.getValue(); i++) {
        LOG(INFO) << "Readed raw transaction numbar << " + i;
        RawTransaction *transaction = new RawTransaction();
        transaction->decode(stream);
        rawTransactions.push_back(*transaction);
        delete transaction;
    }
    LOG(INFO) << "End block read";
}

string Block::toSerealizationForm()
{
  return blockHeader.toSerealizationForm();
}


string Block::toString() {
    stringstream *stream = new stringstream();
    *stream << "-------- BLOCK --------- \n" << "Magic Numbar: " << convertMagicNumbar() << endl;
    *stream << "Block Size: " << blocksize << endl;
    *stream << blockHeader.toString();
    *stream << "Numbar Raw Transaction: " << numbarRawTransaction.getValue() << endl;
    for (int i = 0; i < rawTransactions.size(); i++) {
        *stream << this->rawTransactions.at(i).toString(); //TODO possible generated exception
    }
    string streamResult = stream->str();
    delete  stream;
    return streamResult;
}

string Block::convertMagicNumbar() {
    stringstream *stream = new stringstream();
    *stream << hex << magicNum;
    string magicNumbarString = stream->str();
    delete stream;
    return magicNumbarString;
}

int32_t Block::getMagicNum() const {
    return magicNum;
}

int32_t Block::getBlocksize() const {
    return blocksize;
}

const BlockHeader &Block::getBlockHeader() const {
    return blockHeader;
}

const DVarInt &Block::getNumbarRawTransaction() const {
    return numbarRawTransaction;
}

const vector<RawTransaction> &Block::getRawTransactions() const {
    return rawTransactions;
}

bool Block::operator==(const Block &rhs) const {
    return magicNum == rhs.magicNum &&
           blocksize == rhs.blocksize &&
           blockHeader == rhs.blockHeader;
}

bool Block::operator!=(const Block &rhs) const {
    return !(rhs == *this);
}


