// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <algorithm>

#include <glog/logging.h>

#include "UtilCrypto.h"

using namespace std;

vector<unsigned char> spyCBlock::UtilCrypto::ToHexIntoVectorByte(string &hexData)
{
  LOG(INFO) << "The array Hex is: " << hexData;

  vector<unsigned char> bytes;
  for(unsigned i = 0; i < hexData.length(); i += 2)
  {
      string byteSubString = hexData.substr(i, 2);
      unsigned char byte = static_cast<unsigned char>(strtol(byteSubString.c_str(), nullptr, 16));
      bytes.push_back(byte);

  }
  return bytes;
}





