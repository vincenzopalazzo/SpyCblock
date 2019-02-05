//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include "../transaction/RawTransaction.cpp"
#include "blockHeader.cpp"

#ifndef PARSINGBLOCKCHAIN_BLOCK_H
#define PARSINGBLOCKCHAIN_BLOCK_H

#endif //PARSINGBLOCKCHAIN_BLOCK_H

class Block
{
private:
    int32_t  magicNum;
    int32_t blocksize;
    BlockHeader blockHeader;
    /*TODO left a number of transaction a block*/
    //TODO test, the number is a int32_t, rigth?
    DVarInt numbarRawTransaction;
    std::vector<RawTransaction> rawTransactions;

public:

    const DVarInt &getNumbarRawTransaction() const;

    void setBlockHeader(BlockHeader blockHeader);

    const std::vector<RawTransaction> &getRawTransactions() const;

    bool operator==(const Block &rhs) const;

    bool operator!=(const Block &rhs) const;

    BlockHeader getBlockHeader() const;

    int32_t getMagicNum() const;

    int32_t getBlocksize() const;

    void decode(std::ifstream &stream);
};