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

        void convertBlkIntoJson(string locationBitcoinCore, string destinationBitcoinCoreJson);

    private:

        int currentFile = 0;

        string nameFileSearched(string pathInput);

        string getNameFile(string path);
    };

}

#endif //SPYCBLOCK_SPYCBLOCK_H
