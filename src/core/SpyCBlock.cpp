// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <fstream>
#include <iostream>
#include <type_traits>
#include <experimental/filesystem>

#include <glog/logging.h>
#include "SpyCBlock.h"
#include "../../include/progressbar/include/progressbar/progressbar.h"
#include "../../include/progressbar/include/progressbar/statusbar.h"
#include "../structure/block/Block.h"
#include "../persistence/IDAOBlockchain.h"
#include "../persistence/DAOException.h"
#include "../persistence/graph/transactions/DAOTransactionsGraph.h"
#include "../persistence/json/DAOJson.h"
#include "../persistence/graph/DAOManagerGraph.h"

using namespace spyCBlock;
namespace fs = experimental::filesystem;

template<typename T>
void SpyCBlock::convertData(T &dao, const string &locationBitcoinCore, const string &destinationBitcoinCoreJson) {
    static_assert(std::is_base_of<IDAOBlockchain, T>::value, "T must inherit from IDAOBlockchain");

    if (locationBitcoinCore.empty() || destinationBitcoinCoreJson.empty()) {
        LOG(ERROR) << "The input argument are empty";
        throw exception();
    }


    fs::path bitcoinBlockPath(locationBitcoinCore);
    int fileCount = numberFileInsideThePath(bitcoinBlockPath);

    bool logLevel = ConfiguratorSingleton::getInstance().getLevelLog();
    progressbar *progress = NULL;

    if (logLevel < 3) {
        progress = progressbar_new("Progress", fileCount);
    }


    string pathInput;
    bool isBitcoinDirectory = false;
    string fileExstension = extensionFile(dao);
    LOG(ERROR) << "Exstension file " << fileExstension;
    int end = -1;
    if (howFileWilBeRead != -1) {
        end = currentFile + howFileWilBeRead;
    }
    while ((pathInput = nameFileSearched(locationBitcoinCore, currentFile)) != "") {
        if (howFileWilBeRead != -1 && currentFile == end) {
            LOG(ERROR) << "Readed " << howFileWilBeRead << " files ";
            break;
        }

        try {
            LOG(ERROR) << "Current file blk is " + to_string(currentFile);
            currentFile++;
            string fileNameOutput = getNameFile(pathInput);
            string pathOutput = destinationBitcoinCoreJson + fileNameOutput + fileExstension;
            if (compressionForm && !std::is_same<T, DAOJson>::value) {
                dao.saveBlockCompress(pathInput, pathOutput);
            } else {
                dao.saveBlock(pathInput, pathOutput);
            }
            if (logLevel < 3 && progress != NULL) {
                progressbar_inc(progress);
            }
            isBitcoinDirectory = true;
        } catch (DAOException daoEx) {
            if (isBitcoinDirectory) {
                LOG(ERROR) << "The blk files are finished";
            } else {
                LOG(ERROR) << daoEx.what();
            }
            //break; //If I introducing this I have introducing a condition on the value of block.
            //If i introducing the value break I don't have the possibility to read the value with irregular index
        }
    }
    if (logLevel < 3 && progress != NULL) {
        progressbar_finish(progress);
    } else {
        //If the level log is enabled the progress is not inizialized
        //but in declarated how the pointer, in an better procedure delete it
        delete progress;
    }

}

template<typename T>
void
SpyCBlock::convertDataParallel(T &dao, const string &locationBitcoinCore, const string &destinationBitcoinCoreJson) {
    static_assert(std::is_base_of<IDAOBlockchain, T>::value, "T must inherit from IDAOBlockchain");

    if (locationBitcoinCore.empty() || destinationBitcoinCoreJson.empty()) {
        LOG(ERROR) << "The input argument are empty";
        throw exception();
    }

    //With execution parallel is not posssible set the real height of block, if I set the height = -1 the
    //dao insert inside the information of the link the hash block.
    LOG(ERROR) << "Location path " << locationBitcoinCore;
    fs::path bitcoinBlockPath(locationBitcoinCore);
    std::string fileExstension = extensionFile(dao);
    int fileCount = numberFileInsideThePath(bitcoinBlockPath);
    bool logLevel = ConfiguratorSingleton::getInstance().getLevelLog();
    progressbar *progress = NULL;
    if (logLevel < 3) {
        progress = progressbar_new("Progress", fileCount);
    }

    bool isBitcoinDirectory = false;
    if (howFileWilBeRead != -1) {
        fileCount = currentFile + howFileWilBeRead;
        LOG(ERROR) << "from file " << currentFile << " to file " << fileCount;
    } else {
        fileCount += currentFile;
    }

    #pragma omp parallel for
    for (int i = currentFile; i < fileCount; i++) {
        try {
            string pathInput = nameFileSearched(locationBitcoinCore, i);
            LOG(INFO) << pathInput;
            string fileNameOutput = getNameFile(pathInput);
            string pathOutput = destinationBitcoinCoreJson + fileNameOutput + fileExstension;
            LOG(INFO) << pathOutput;
            if (compressionForm && !std::is_same<T, DAOJson>::value) {
                dao.saveBlockCompress(pathInput, pathOutput);
            } else {
                dao.saveBlock(pathInput, pathOutput);
            }
            isBitcoinDirectory = true;
            if (logLevel < 3 && progress != NULL) {
                #pragma omp critical
                {
                    progressbar_inc(progress);
                }
            }
        } catch (DAOException daoEx) {
            if (isBitcoinDirectory) {
                LOG(ERROR) << "The blk files are finished";
            } else {
                LOG(ERROR) << daoEx.what();
            }
            //break; //If I introducing this I have introducing a condition on the value of block.
            //If i introducing the value break I don't have the possibility to read the value with irregular index
        }
    }
    if (logLevel < 3 && progress != NULL) {
        progressbar_finish(progress);
    } else {
        //If the level log is enabled the progress is not inizialized
        //but in declarated how the pointer, in an better procedure delete it
        delete progress;
    }
}

//I can remove this method and add support to the library of C++17 <filesystem>
string SpyCBlock::nameFileSearched(const string &pathInput, int &currentFile) {
    if (pathInput.empty()) {
        LOG(ERROR) << "Input function null";
        throw exception();
    }
    LOG(ERROR) << "Attual value current file blk: " << currentFile;
    //Search file blk.dat
    //TODO The path must be have the /, this is an future fix
    if (currentFile < 10) {
        return pathInput + "blk0000" + to_string(currentFile) + ".dat";
    } else if (currentFile < 100) {
        return pathInput + "blk000" + to_string(currentFile) + ".dat";
    } else if (currentFile < 1000) {
        return pathInput + "blk00" + to_string(currentFile) + ".dat";
    } else if (currentFile < 10000) {
        return pathInput + "blk0" + to_string(currentFile) + ".dat";
    } else if (currentFile < 100000) {
        return pathInput + "blk0" + to_string(currentFile) + ".dat";
    }
    LOG(ERROR) << "The current file is greater to 100000, the value current file is:" << currentFile;
    return "";
}

string SpyCBlock::getNameFile(const string &path) {
    LOG(INFO) << "Path File is " << path;
    string nameFile = path.substr((path.size() - 12), 8);
    LOG(WARNING) << "Name file analized is " << nameFile << "and creating file json whit this name";
    LOG_IF(ERROR, nameFile.empty()) << "Name file empity";
    return nameFile;
}

template<typename T>
string SpyCBlock::extensionFile(T &dao) {
    if (std::is_base_of<DAOJson, T>::value) {
        return ".json";
    } else {
        if (compressionForm) { return ".dat"; }
        return ".txt";
    }
}


template void SpyCBlock::convertData<DAOManagerGraph>(DAOManagerGraph &dao, const string &locationBitcoinCore,
                                                      const string &destinationBitcoinCoreJson);

template void SpyCBlock::convertData<DAOJson>(DAOJson &dao, const string &locationBitcoinCore,
                                              const string &destinationBitcoinCoreJson);

template void SpyCBlock::convertData<DAOTransactionsGraph>(DAOTransactionsGraph &dao,
                                                           const string &locationBitcoinCore,
                                                           const string &destinationBitcoinCoreJson);

template void SpyCBlock::convertDataParallel<DAOManagerGraph>(DAOManagerGraph &dao, const string &locationBitcoinCore,
                                                              const string &destinationBitcoinCoreJson);

template void SpyCBlock::convertDataParallel<DAOJson>(DAOJson &dao, const string &locationBitcoinCore,
                                                      const string &destinationBitcoinCoreJson);

template void SpyCBlock::convertDataParallel<DAOTransactionsGraph>(DAOTransactionsGraph &dao,
                                                                   const string &locationBitcoinCore,
                                                                   const string &destinationBitcoinCoreJson);

template string SpyCBlock::exstensionFile<DAOManagerGraph>(DAOManagerGraph &dao);

template string SpyCBlock::exstensionFile<DAOJson>(DAOJson &dao);

template string SpyCBlock::exstensionFile<DAOTransactionsGraph>(DAOTransactionsGraph &dao);



