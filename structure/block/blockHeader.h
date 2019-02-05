//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#include "../../util/uint256.h"

#ifndef PARSINGBLOCKCHAIN_BLOCKHEADER_H
#define PARSINGBLOCKCHAIN_BLOCKHEADER_H

#endif //PARSINGBLOCKCHAIN_BLOCKHEADER_H

/**
 * The dimension blockheader is 80 bit
 */
class BlockHeader
{
private:
    int32_t version;
    uint256 previousBlockHeaderHash;
    uint256 merkleRoot;
    uint32_t time;
    uint32_t nBits; // this whats corrisponde
    uint32_t nonce;

public:
    virtual ~BlockHeader();

    BlockHeader();

    BlockHeader(int32_t version, uint256 previousBlockHeaderHash, uint256 merkleRoot, uint32_t time, uint32_t nBits, uint32_t nonce);

    int32_t getVersion();

    uint32_t getTime() const;

    uint32_t getNBits() const;

    uint32_t getNonce() const;

    const uint256 &getPreviousBlockHeaderHash() const;

    const uint256 &getMerkleRoot() const;

    bool operator==(const BlockHeader &rhs) const;

    bool operator!=(const BlockHeader &rhs) const;

    void unserialize(std::ifstream &stream);

};