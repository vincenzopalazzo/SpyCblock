//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <cstdint>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <locale>
#include <cmath>
#include "blockHeader.h"
#include "../../util/serialize.h"


int32_t BlockHeader::getVersion() {
    return version;
}


uint32_t BlockHeader::getTime() const {
    return time;
}

uint32_t BlockHeader::getNBits() const {
    return nBits;
}

uint32_t BlockHeader::getNonce() const {
    return nonce;
}



BlockHeader::BlockHeader(int32_t version, uint256 previousBlockHeaderHash, uint256 merkleRoot, uint32_t time,
                         uint32_t nBits, uint32_t nonce) {
    this->version = version;
    this->previousBlockHeaderHash = previousBlockHeaderHash;
    this->merkleRoot = merkleRoot;
    this->time = time;
    this->nBits = nBits;
    this->nonce = nonce;
}

const uint256 &BlockHeader::getPreviousBlockHeaderHash() const {
    return previousBlockHeaderHash;
}

const uint256 &BlockHeader::getMerkleRoot() const {
    return merkleRoot;
}

BlockHeader::BlockHeader() {}

BlockHeader::~BlockHeader() {

}

bool BlockHeader::operator==(const BlockHeader &rhs) const {
    return version == rhs.version &&
           previousBlockHeaderHash == rhs.previousBlockHeaderHash &&
           merkleRoot == rhs.merkleRoot &&
           time == rhs.time &&
           nBits == rhs.nBits &&
           nonce == rhs.nonce;
}

bool BlockHeader::operator!=(const BlockHeader &rhs) const {
    return !(rhs == *this);
}

void BlockHeader::unserialize(std::ifstream &stream)
{
    Unserialize(stream, version);
    this->previousBlockHeaderHash.Unserialize(stream);
    this->merkleRoot.Unserialize(stream);
    Unserialize(stream, this->time);
    Unserialize(stream, this->nBits);
    Unserialize(stream, this->nonce);
}


