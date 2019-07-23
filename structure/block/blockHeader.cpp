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
#include "../../persistence/SerializationUtil.h"

using namespace spyCBlock;
using namespace std;
using namespace nlohmann;

//TODO remove this method
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

BlockHeader::BlockHeader(){}

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
    LOG(INFO) << "Time stamp block readed: " << time;
    Unserialize(stream, this->nBits);
    LOG(INFO) << "NBits block readed: " << nBits;
    Unserialize(stream, this->nonce);
    LOG(INFO) << "Nonce block readed: " << nonce;
}

string BlockHeader::toSerealizationForm()
{
  string hexForm = SerializationUtil::toSerealizeForm(this->version);
  hexForm += SerializationUtil::toSerealizeForm(this->getPreviousBlockHeaderHash());
  hexForm += SerializationUtil::toSerealizeForm(this->getMerkleRoot());
  hexForm += SerializationUtil::toSerealizeForm(this->time);
  hexForm += SerializationUtil::toSerealizeForm(this->nBits);
  hexForm += SerializationUtil::toSerealizeForm(this->nonce);
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

void BlockHeader::toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson)
{
  writerJson.StartObject();

  writerJson.Key("version");
  writerJson.Int(this->version);

  writerJson.Key("previusBlockHeaderHash");
  writerJson.String(this->previousBlockHeaderHash.ToString().c_str());

  writerJson.Key("markleRoot");
  writerJson.String(this->merkleRoot.ToString().c_str());

  writerJson.Key("time");
  writerJson.Int(this->time);

  writerJson.Key("nBits");
  writerJson.Uint(this->nBits);

  writerJson.Key("nonce");
  writerJson.Uint(this->nonce);

  writerJson.EndObject();
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

