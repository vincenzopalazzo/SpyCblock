//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#ifndef PARSINGBLOCKCHAIN_BLOCKHEADER_H
#define PARSINGBLOCKCHAIN_BLOCKHEADER_H

#include "../../util/uint256.h"
#include <glog/logging.h>
#include "../../util/serialize.h"
//#include "../../persistence/serializationutil.h"

using namespace std;
//using namespace spyCBlock;

/**
 * The dimension blockheader is 80 bit
 */
class BlockHeader
{
private:
    int32_t version;
    uint256 previousBlockHeaderHash;
    uint256 merkleRoot;
    int32_t time;
    uint32_t nBits; // this whats corrisponde
    uint32_t nonce;

    string convertTimeStamp();

public:
    virtual ~BlockHeader();

    BlockHeader();

    BlockHeader(int32_t version, uint256 previousBlockHeaderHash, uint256 merkleRoot, uint32_t time, uint32_t nBits, uint32_t nonce);

    int32_t getVersion() const ;

    uint32_t getTime() const;

    uint32_t getNBits() const;

    uint32_t getNonce() const;

    const uint256 &getPreviousBlockHeaderHash() const;

    const uint256 &getMerkleRoot() const;

    bool operator==(const BlockHeader &rhs) const;

    bool operator!=(const BlockHeader &rhs) const;

    string toString();

    void unserialize(std::ifstream &stream);

    string toSerealizationForm();

};

#endif //PARSINGBLOCKCHAIN_BLOCKHEADER_H
