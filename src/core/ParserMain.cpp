// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <glog/logging.h>

#include "SpyCBlock.h"
#include "ConfiguratorSingleton.h"
#include "../persistence/IDAOBlockchain.h"
#include "../persistence/json/DAOJson.h"
#include "../persistence/graph/transactions/DAOTransactionsGraph.h"
#include "../persistence/graph/DAOManagerGraph.h"

using namespace google;
using namespace spyCBlock;

using namespace std;

const std::string JSON_DECODE = "jsondecode";
const std::string GRAPH_TX = "graphtx";
const std::string GRAPH_PUB_KEY = "graphpubkey";

int main(int argc, char* argv[])
{
    FLAGS_minloglevel = 2; //TODO configure  the log from file configuration
    FLAGS_logtostderr = false;
    google::InitGoogleLogging("2");
    string pathLogFile = ConfiguratorSingleton::getInstance().getPathFileLog() + "/main_log.log";
    google::SetLogDestination(google::GLOG_ERROR, pathLogFile.c_str());

    SpyCBlock spyCBlock = SpyCBlock();

    //TODO add configuration to command line

    std::string settingDecodeType = ConfiguratorSingleton::getInstance().getFormatFileDecode();
    LOG(ERROR) << "The type of decode is: " << settingDecodeType;
    if(settingDecodeType == JSON_DECODE){
        DAOJson dao;
        spyCBlock.convertData(dao, ConfiguratorSingleton::getInstance().getPathBlockDat() + "/",
                              ConfiguratorSingleton::getInstance().getPathBlockDecode() + "/");
        return EXIT_SUCCESS;
    }else if (settingDecodeType == GRAPH_TX){
        DAOTransactionsGraph dao;
        spyCBlock.convertData(dao, ConfiguratorSingleton::getInstance().getPathBlockDat() + "/",
                                 ConfiguratorSingleton::getInstance().getPathBlockDecode() + "/");
        return EXIT_SUCCESS;
    }else if(settingDecodeType == GRAPH_PUB_KEY){
        DAOManagerGraph dao;
        spyCBlock.convertData(dao, ConfiguratorSingleton::getInstance().getPathBlockDat() + "/",
                              ConfiguratorSingleton::getInstance().getPathBlockDecode() + "/");
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
