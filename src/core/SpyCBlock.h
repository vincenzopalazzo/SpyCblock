// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SPYCBLOCK_SPYCBLOCK_H
#define SPYCBLOCK_SPYCBLOCK_H

#include <string>

#include "ConfiguratorSingleton.h"
#include "../persistence/IDAOBlockchain.h"

namespace spyCBlock {

    class SpyCBlock {

        public:

            [[deprecated]] void convertBlkIntoJson(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            [[deprecated]] void convertBlkIntoGraphForm(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            [[deprecated]] void convertBlkIntoGraphFormPubKey(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            template<typename T>
            void convertData(T dao, const std::string &locationBitcoinCore, const std::string &destinationBitcoinCoreJson);

            template<typename T>
            std::string exstensionFile(T dao);
        private:

            int currentFile = ConfiguratorSingleton::getInstance().getStartHeightBlock();

            std::string nameFileSearched(const std::string &pathInput);

            std::string getNameFile(const std::string &path);
    };

}

#endif //SPYCBLOCK_SPYCBLOCK_H
