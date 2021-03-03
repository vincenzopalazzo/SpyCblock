// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "UtilCrypto.h"

#include <glog/logging.h>

#include <algorithm>
#include <iomanip>

#include "../DefinitionMacro.h"

using namespace std;

vector<unsigned char> spyCBlock::UtilCrypto::FromHexToBytes(
    string const& hexData) {
  LOG(INFO) << "The array Hex is: " << hexData;

  vector<unsigned char> bytes;
  bytes.reserve(hexData.length() / 2);
  for (unsigned i = 0; i < hexData.length(); i += 2) {
    string byteSubString = hexData.substr(i, 2);
    unsigned char byte =
        static_cast<unsigned char>(strtol(byteSubString.c_str(), nullptr, 16));
    bytes.emplace_back(byte);
  }
  return bytes;
}

vector<unsigned char> spyCBlock::UtilCrypto::FromStringToByte(
    const string& genericString) {
  return vector<unsigned char>(genericString.begin(), genericString.end());
}

std::string spyCBlock::UtilCrypto::BytesLittleEndianToStringBigEndian(
    vector<unsigned char> const& bytes) {
  return UtilCrypto::BytesLittleEndianToStringBigEndian(bytes, 0, bytes.size());
}

std::string spyCBlock::UtilCrypto::BytesLittleEndianToStringBigEndian(
    const vector<unsigned char>& bytes, std::size_t start, std::size_t end) {
  std::vector<unsigned char> bigEndian;
  bigEndian.reserve(bytes.size());
  for (int i = end; i >= start; i--) {
    bigEndian.push_back(bytes.at(i));
  }
  std::stringstream stream;
  for (int i = 0; i < bigEndian.size(); i++) {
    auto valueInt = static_cast<unsigned int>(bigEndian[i]);
    stream << std::hex << std::setfill('0') << std::setprecision(2)
           << std::setw(2) << valueInt;
  }
  return stream.str();
}
