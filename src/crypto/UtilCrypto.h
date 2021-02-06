// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef UTILCRYPTO_H
#define UTILCRYPTO_H

#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace spyCBlock {

class UtilCrypto {
 public:
  static vector<unsigned char> FromHexToBytes(string const &hexData);

  static vector<unsigned char> FromStringToByte(string const &genericString);

  static std::string BytesLittleEndianToStringBigEndian(
      std::vector<unsigned char> const &bytes);

  static std::string BytesLittleEndianToStringBigEndian(
      std::vector<unsigned char> const &bytes, std::size_t start,
      std::size_t end);
};

}  // namespace spyCBlock
#endif  // UTILCRYPTO_H
