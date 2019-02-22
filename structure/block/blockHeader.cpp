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
    LOG(INFO) << "Version block header readed: " << version;
   this->previousBlockHeaderHash.Unserialize(stream);
    LOG(INFO) << "Privius block readed: " << previousBlockHeaderHash.ToString();
    this->merkleRoot.Unserialize(stream);
    LOG(INFO) << "Merkler root readed: " << merkleRoot.ToString();
    Unserialize(stream, this->time);
    LOG(INFO) << "Time stamp block readed: " << previousBlockHeaderHash.ToString();
    Unserialize(stream, this->nBits);
    LOG(INFO) << "NBits block readed: " << previousBlockHeaderHash.ToString();
    Unserialize(stream, this->nonce);
    LOG(INFO) << "Nonce block readed: " << previousBlockHeaderHash.ToString();
}

string BlockHeader::toString() {
    stringstream stream;
    stream << "---------- Block Header ---------- \n" << "Version: " << version << endl;
    stream << "Previous Block Header Hash: " << previousBlockHeaderHash.GetHex() << endl;
    stream << "Merkle Root: " << merkleRoot.GetHex() << endl;
    stream << "Time: " << convertTimeStamp() << endl;
    stream << "nBits: " << nBits << endl;
    stream << "Nonce: " << nonce << endl;
    return stream.str();
}

string BlockHeader::convertTimeStamp() {
    char data[30];
    time_t timeToValue = time;
    tm *tmTime = gmtime(&timeToValue);
    strftime (data,30,"%F %T", tmTime);
    string dataString = string(data);
    return dataString;
}

const uint256 &BlockHeader::getPreviousBlockHeaderHash() const {
    return previousBlockHeaderHash;
}

const uint256 &BlockHeader::getMerkleRoot() const {
    return merkleRoot;
}


