/**
  *@author https://github.com/vincenzopalazzo in 23/03/2019
*/

#ifndef CRYPTOSINGLETON_H
#define CRYPTOSINGLETON_H

#include <string>

using namespace std;

namespace spyCBlock {

    class CryptoSingleton
    {
      public:
        static CryptoSingleton& getIstance(){
            static CryptoSingleton SINGLETON;
        }

        string getHash256(string baseHash);

      private:
        CryptoSingleton(){}
    };
}


#endif // CRYPTOSINGLETON_H
