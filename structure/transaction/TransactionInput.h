//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <cstdint>
#include "../../type/Outpoint.cpp"
#include "../../type/DScript.cpp"

#ifndef PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H
#define PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

#endif //PARSINGBLOCKCHAIN_TXINNOCOINDBASE_H

//TODO refactoring whit tipe bitcoin core
/*
 * In the coindbase transaction, outpoint is standard, the hash id resiver si 0 and
 * the n is 2^32 - 1*/
class TransactionInput
{
private:
    OutPoint outpoint;
    DScript script;
    uint32_t sequences;
public:
    const DScript &getScript() const;

    uint32_t getSequences() const;

    const OutPoint &getOutpoint() const;

    void setOutpoint(const OutPoint &outpoint);

    void decode(std::ifstream &stream);
};