// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "CryptoCore.h"

#include <glog/logging.h>

#include "../../include/bitcoin-cryptography-library/cpp/Sha256.hpp"
#include "../../include/bitcoin-cryptography-library/cpp/Sha256Hash.hpp"
#include "../DefinitionMacro.h"
#include "../crypto/UtilCrypto.h"

using namespace spyCBlock;

string CryptoSingleton::getHash256(string const& baseHash) {
  assertf(baseHash.length() > 0,
          "Argument function getHash256 of CryptoSingleton is not valid");

  LOG(INFO) << "The baseHash is " << baseHash;

  vector<unsigned char> vectorByte =
      spyCBlock::UtilCrypto::FromHexToBytes(baseHash);
  Sha256Hash shaHash =
      Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

  return shaHash.ToStringForProtocol();
}
