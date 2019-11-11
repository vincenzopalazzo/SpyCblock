// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SPYCBLOCK_SPYCBLOCK_H
#define SPYCBLOCK_SPYCBLOCK_H

#include <string>

#include "ConfiguratorSingleton.h"
#include "../persistence/IDAOBlockchain.h"

namespace spyCBlock
{
    class SpyCBlock
    {
        public:

            [[deprecated]] void convertBlkIntoJson(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            [[deprecated]] void convertBlkIntoGraphForm(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            [[deprecated]] void convertBlkIntoGraphFormPubKey(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

            template<typename T>
            void convertData(T &dao, const std::string &locationBitcoinCore, const std::string &destinationBitcoinCoreJson);

            template<typename T>
            void convertDataParallel(T &dao, const std::string &locationBitcoinCore, const std::string &destinationBitcoinCoreJson);

            template<typename T>
            std::string exstensionFile(T &dao);

            inline void setHowFileWilBeRead(int value){
              this->howFileWilBeRead = value;
            }

            inline void resetFileToStartReadNum(){
              fileToStartRead = 0;
              currentFile = ConfiguratorSingleton::getInstance().getStartHeightBlock();
            }

            inline void setCompressed(bool value){
                 this->compressionForm = value;
            }

        private:

            int currentFile = ConfiguratorSingleton::getInstance().getStartHeightBlock();

            int fileToStartRead = 0;

            std::string nameFileSearched(const std::string &pathInput, int &currentFile);

            std::string getNameFile(const std::string &path);

            int howFileWilBeRead = ConfiguratorSingleton::getInstance().getHowManyFileWouldBeRead();

            bool compressionForm = ConfiguratorSingleton::getInstance().isCompressionResult();
    };

}

#endif //SPYCBLOCK_SPYCBLOCK_H
