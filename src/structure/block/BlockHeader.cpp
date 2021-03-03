// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt
#include "BlockHeader.h"

#include <cmath>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>

#include "../../persistence/SerializationUtil.h"

using namespace spyCBlock;
using namespace std;

void BlockHeader::decode(std::ifstream& stream) {
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

string BlockHeader::toSerealizationForm() {
  string hexForm = SerializationUtil::toSerializeForm(this->version);
  hexForm +=
      SerializationUtil::toSerializeForm(this->getPreviousBlockHeaderHash());
  hexForm += SerializationUtil::toSerializeForm(this->getMerkleRoot());
  hexForm += SerializationUtil::toSerializeForm(this->time);
  hexForm += SerializationUtil::toSerializeForm(this->nBits);
  hexForm += SerializationUtil::toSerializeForm(this->nonce);
  return hexForm;
}

void BlockHeader::toJson(
    rapidjson::Writer<rapidjson::OStreamWrapper>& writerJson) {
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

string BlockHeader::toString() {
  string stringForm = "---------- Block Header ---------- \n";
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

string BlockHeader::convertTimeStamp() {
  char data[30];
  time_t timeToValue = time;
  tm* tmTime = gmtime(&timeToValue);
  strftime(data, 30, "%F %T", tmTime);
  string dataString = string(data);
  return dataString;
}

// Getter and Setter
int32_t BlockHeader::getVersion() const { return version; }

uint32_t BlockHeader::getTime() const {
  return static_cast<const uint32_t>(time);
}

uint32_t BlockHeader::getNBits() const { return nBits; }

uint32_t BlockHeader::getNonce() const { return nonce; }

const uint256& BlockHeader::getPreviousBlockHeaderHash() const {
  return previousBlockHeaderHash;
}

const uint256& BlockHeader::getMerkleRoot() const { return merkleRoot; }

bool BlockHeader::operator==(const BlockHeader& rhs) const {
  return version == rhs.version &&
         previousBlockHeaderHash == rhs.previousBlockHeaderHash &&
         merkleRoot == rhs.merkleRoot && time == rhs.time &&
         nBits == rhs.nBits && nonce == rhs.nonce;
}

bool BlockHeader::operator!=(const BlockHeader& rhs) const {
  return !(rhs == *this);
}
