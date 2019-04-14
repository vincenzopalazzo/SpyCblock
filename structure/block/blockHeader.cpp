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
#include "../../persistence/serializationutil.h"

using namespace spyCBlock;

BlockHeader::BlockHeader(int32_t version, uint256 previousBlockHeaderHash, uint256 merkleRoot, uint32_t time,
                         uint32_t nBits, uint32_t nonce)
{
    this->version = version;
    this->previousBlockHeaderHash = previousBlockHeaderHash;
    this->merkleRoot = merkleRoot;
    this->time = time;
    this->nBits = nBits;
    this->nonce = nonce;
}

BlockHeader::BlockHeader()
{}

BlockHeader::~BlockHeader()
{}

int32_t BlockHeader::getVersion() const
{
    return version;
}

uint32_t BlockHeader::getTime() const
{
    return static_cast<const uint32_t>(time);
}

uint32_t BlockHeader::getNBits() const
{
    return nBits;
}

uint32_t BlockHeader::getNonce() const
{
    return nonce;
}

const uint256 &BlockHeader::getPreviousBlockHeaderHash() const {
    return previousBlockHeaderHash;
}

const uint256 &BlockHeader::getMerkleRoot() const {
    return merkleRoot;
}

bool BlockHeader::operator==(const BlockHeader &rhs) const
{
    return version == rhs.version &&
           previousBlockHeaderHash == rhs.previousBlockHeaderHash &&
           merkleRoot == rhs.merkleRoot &&
           time == rhs.time &&
           nBits == rhs.nBits &&
           nonce == rhs.nonce;
}

bool BlockHeader::operator!=(const BlockHeader &rhs) const
{
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

string BlockHeader::toSerealizationForm()
{
  string hexForm = SerializationUtilSingleton::getInstance()->toSerealizeForm(this->version);
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->getPreviousBlockHeaderHash());
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->getMerkleRoot());
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->time);
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->nBits);
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->nonce);
  return hexForm;
}

json BlockHeader::toJoson()
{
  return json::object({
                        {"version", version},
                        {"previusBlockHeaderHash", this->previousBlockHeaderHash.GetHex()},
                        {"markleRoot", this->merkleRoot.GetHex()},
                        {"time", this->time},
                        {"nBits", this->nBits},
                        {"nonce", this->nonce},
                      });
}

string BlockHeader::toString()
{
    string stringForm =  "---------- Block Header ---------- \n";
    stringForm += "Version: ";
    stringForm += to_string(version);
    stringForm += "\n";
    stringForm += "Previous Block Header Hash: ";
    stringForm += previousBlockHeaderHash.GetHex();
    stringForm += "\n";
    stringForm += "Merkle Root: ";
    stringForm += merkleRoot.GetHex();
    stringForm += "\n";
    stringForm += "Time: ";
    stringForm += convertTimeStamp();
    stringForm += "\n";
    stringForm += "nBits: ";
    stringForm += to_string(nBits);
    stringForm += "\n";
    stringForm += "Nonce: ";
    stringForm += to_string(nonce);
    return stringForm;
}

string BlockHeader::convertTimeStamp()
{
    char data[30];
    time_t timeToValue = time;
    tm *tmTime = gmtime(&timeToValue);
    strftime (data,30,"%F %T", tmTime);
    string dataString = string(data);
    return dataString;
}

