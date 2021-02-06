// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef CRYPTOSINGLETON_H
#define CRYPTOSINGLETON_H

#include <string>

using byte = std::uint8_t;
// Base implementation encode and decode base 64 is
// proposed by https://github.com/mvorbrodt/blog/blob/master/src/base64.hpp
namespace spyCBlock {
class CryptoSingleton {
 public:
  static CryptoSingleton &getInstance() {
    static CryptoSingleton SINGLETON;
    return SINGLETON;
  }

  std::string getHash256(std::string const &baseHash);

 private:
  CryptoSingleton() = default;
};
}  // namespace spyCBlock
#endif  // CRYPTOSINGLETON_H
