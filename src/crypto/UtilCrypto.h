// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef UTILCRYPTO_H
#define UTILCRYPTO_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace spyCBlock {

    class UtilCrypto {
    public:
        static vector<unsigned char> ToHexIntoVectorByte(string &hexData);
    };

}
#endif // UTILCRYPTO_H
