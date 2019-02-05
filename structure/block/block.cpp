//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <iostream>
#include <regex>
#include "block.h"
#include <glog/logging.h>

const std::vector<RawTransaction> &Block::getRawTransactions() const {
    return rawTransactions;
}

bool Block::operator==(const Block &rhs) const {
    return blockHeader == rhs.blockHeader;
}

bool Block::operator!=(const Block &rhs) const {
    return !(rhs == *this);
}

BlockHeader Block::getBlockHeader() const {
    return blockHeader;
}

void Block::decode(std::ifstream &stream)
{
    Unserialize(stream, this->magicNum);
    Unserialize(stream, this->blocksize);
    blockHeader.unserialize(stream);
    this->numbarRawTransaction.decode(stream);
    //TODO deserialize transaction
    if(numbarRawTransaction.getValue() == -1){
        //TODO segnalare errore
        return;
    }
    for(int i = 0; i < numbarRawTransaction.getValue(); i++){
        rawTransactions.clear();
        RawTransaction transaction = RawTransaction();
        transaction.decode(stream);
        rawTransactions.push_back(transaction);
        std::cout << "**** " << rawTransactions.size();
    }
}



int32_t Block::getMagicNum() const {
    return magicNum;
}

int32_t Block::getBlocksize() const {
    return blocksize;
}

void Block::setBlockHeader(BlockHeader blockHeader) {
    Block::blockHeader = blockHeader;
}

const DVarInt &Block::getNumbarRawTransaction() const {
    return numbarRawTransaction;
}


