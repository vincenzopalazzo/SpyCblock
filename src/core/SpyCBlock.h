// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SPYCBLOCK_SPYCBLOCK_H
#define SPYCBLOCK_SPYCBLOCK_H

#include <experimental/filesystem>
#include <string>

#include "../DefinitionMacro.h"
#include "../persistence/IDAOBlockchain.h"
#include "ConfiguratorSingleton.h"

namespace spyCBlock {
class SpyCBlock {
 public:
  template <typename T>
  void convertData(T& dao, const std::string& locationBitcoinCore,
                   const std::string& destinationBitcoinCoreJson);

  template <typename T>
  void convertDataParallel(T& dao, const std::string& locationBitcoinCore,
                           const std::string& destinationBitcoinCoreJson);

  template <typename T>
  void convertChainState(T& dao, const std::string& pathLoadDirectory,
                         const std::string& destinationDirectory);

  template <typename T>
  std::string extensionFile(T& dao);

  inline void setHowFileWilBeRead(int value) { this->howFileWilBeRead = value; }

  inline void resetFileToStartReadNum() {
    currentFile = ConfiguratorSingleton::getInstance().getStartHeightBlock();
  }

  inline void setCompressed(bool value) { this->compressionForm = value; }

 private:
  int currentFile = ConfiguratorSingleton::getInstance().getStartHeightBlock();

  std::string nameFileSearched(const std::string& pathInput, int& currentFile);

  std::string getNameFile(const std::string& path);

  int howFileWilBeRead =
      ConfiguratorSingleton::getInstance().getHowManyFileWouldBeRead();

  bool compressionForm =
      ConfiguratorSingleton::getInstance().isCompressionResult();

  int numberFileInsidePath(std::experimental::filesystem::path path,
                           bool isChainState) {
    assertf(!path.empty(), "The path is empty");
    int fileCount = 0;
    for (auto fileBlk :
         std::experimental::filesystem::directory_iterator(path)) {
      std::string fileName = fileBlk.path().filename();
      if (!std::experimental::filesystem::is_directory(fileBlk)) {
        if (isChainState) {
          fileCount++;
        } else if (fileName.find("blk") != std::string::npos) {
          fileCount++;
        }
      }
    }
    return fileCount;
  }

  int numberFileInsidePath(std::experimental::filesystem::path path) {
    return numberFileInsidePath(path, false);
  }
};

}  // namespace spyCBlock

#endif  // SPYCBLOCK_SPYCBLOCK_H
