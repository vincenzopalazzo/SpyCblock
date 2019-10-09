// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SPYCBLOCK_SPYCBLOCK_H
#define SPYCBLOCK_SPYCBLOCK_H

#include <string>

#include "ConfiguratorSingleton.h"


namespace spyCBlock {

    class SpyCBlock {

        public:

            void convertBlkIntoJson(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            void convertBlkIntoGraphForm(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            void convertBlkIntoGraphFormPubKey(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);
        private:

            int currentFile = ConfiguratorSingleton::getInstance().getStartHeightBlock();

            std::string nameFileSearched(std::string &pathInput);

            std::string getNameFile(std::string &path);
    };

}

#endif //SPYCBLOCK_SPYCBLOCK_H
