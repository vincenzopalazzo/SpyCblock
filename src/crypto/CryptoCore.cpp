// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <glog/logging.h>

#include "CryptoCore.h"
#include "../crypto/UtilCrypto.h"
#include "../../include/bitcoin-cryptography-library/cpp/Sha256Hash.hpp"
#include "../../include/bitcoin-cryptography-library/cpp/Sha256.hpp"
#include "../DefinitionMacro.h"

using namespace spyCBlock;

string CryptoSingleton::getHash256(string baseHash)
{
  assertf(baseHash.length() > 0, "Argument function getHash256 of CryptoSingleton is not valid");

  LOG(INFO) << "The baseHash is " << baseHash;

  vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(baseHash);
  Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

  return shaHash.ToStringForProtocol();
}

