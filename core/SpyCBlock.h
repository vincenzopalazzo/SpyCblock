//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#ifndef SPYCBLOCK_SPYCBLOCK_H
#define SPYCBLOCK_SPYCBLOCK_H

#include <string>

using namespace std;

namespace spyCBlock {

    class SpyCBlock {

    public:
        //TODO this method refactoring
        void read(string pathBlockchain);

        bool convertBlockchainToJson(string locationBitcoinCore, string destinationBitcoinCoreJson);

    };

}

#endif //SPYCBLOCK_SPYCBLOCK_H
