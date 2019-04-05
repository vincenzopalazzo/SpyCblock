#include <glog/logging.h>
#include "cryptosingleton.h"
#include "../crypto/utilcrypto.h"
#include "../cryptobitcoin/Sha256Hash.hpp"
#include "../cryptobitcoin/Sha256.hpp"

using namespace spyCBlock;

CryptoSingleton* CryptoSingleton::SINGLETON = nullptr; //Se levi questo causi errore sintattico ma perchè?

CryptoSingleton *CryptoSingleton::getIstance()
{
  if(CryptoSingleton::SINGLETON == nullptr)
  {
    CryptoSingleton::SINGLETON = new CryptoSingleton();
  }
  return CryptoSingleton::SINGLETON;
}

//TODO testing this function.
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

CryptoSingleton::CryptoSingleton() {
}

