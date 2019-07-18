#include <glog/logging.h>

#include "CryptoCore.h"
#include "../crypto/UtilCrypto.h"
#include "../cryptobitcoin/Sha256Hash.hpp"
#include "../cryptobitcoin/Sha256.hpp"

using namespace spyCBlock;

string CryptoSingleton::getHash256(string baseHash)
{
  if(baseHash.length() <= 0)
  {
    throw "Argument function getHash256 of CryptoSingleton is not valid";
  }
  LOG(WARNING) << "The baseHash is " << baseHash;

  vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(baseHash);
  Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

  return shaHash.ToStringForProtocol();
}

