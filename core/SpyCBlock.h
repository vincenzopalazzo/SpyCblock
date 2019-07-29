//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#ifndef SPYCBLOCK_SPYCBLOCK_H
#define SPYCBLOCK_SPYCBLOCK_H

#include <string>


namespace spyCBlock {

    class SpyCBlock {

        public:
            //TODO this method refactoring
            void read(std::string pathBlockchain);

            void convertBlkIntoJson(std::string locationBitcoinCore, std::string destinationBitcoinCoreJson);

        private:

            int currentFile = 0;

            std::string nameFileSearched(std::string &pathInput);

            std::string getNameFile(std::string &path);
    };

}

#endif //SPYCBLOCK_SPYCBLOCK_H
