// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef CRYPTOSINGLETON_H
#define CRYPTOSINGLETON_H

#include <string>

using namespace std;

namespace spyCBlock {
    class CryptoSingleton {
    public:

        static CryptoSingleton &getIstance() {
            static CryptoSingleton SINGLETON;
            return SINGLETON;
        }

        string getHash256(string baseHash);

    private:

        CryptoSingleton() {}
    };
}


#endif // CRYPTOSINGLETON_H
