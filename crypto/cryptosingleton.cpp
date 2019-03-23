#include <glog/logging.h>
#include "cryptosingleton.h"
#include "cryptopp/cryptlib.h"

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

string* CryptoSingleton::getHash256(string *baseHash)
{
  if(baseHash == nullptr)
  {
    throw "Argument function getHash256 of CryptoSingleton is null";
  }
  LOG(WARNING) << "The baseHash is " << *baseHash;

  return nullptr;
}

CryptoSingleton::CryptoSingleton() {
}

