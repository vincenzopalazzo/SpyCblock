// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <experimental/filesystem>
#include <chrono>

#include <glog/logging.h>
#include "../../../../include/spycblockrpc/src/core/graph/WrapperInformations.h"

#include "DAOTransactionsGraph.h"
#include "../../DAOException.h"
#include "../../../core/ConfiguratorSingleton.h"

using namespace std;
namespace fs = std::experimental::filesystem;
using namespace chrono;

bool spyCBlock::DAOTransactionsGraph::saveBlock(string inputPath, string outputPath, int &height)
{
  if(inputPath.empty() || outputPath.empty()){
    LOG(ERROR) << "Error, the input argument are empty";
    throw DAOException("Error, the input argument are empty");
  }

  if (fs::exists(inputPath)){
      if(!fs::is_directory(inputPath)){
          ifstream loadFileDat(inputPath);
          ofstream saveBlkToJson(outputPath);  //Can same file? or create an file for file blk?
          if(!saveBlkToJson.is_open()){
              LOG(ERROR) << "The file output not open " + outputPath;
              throw DAOException("The file output not open in tha path " + outputPath);
          }

          if(loadFileDat.is_open()){
            Block block;
            chrono::milliseconds start = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            while(!loadFileDat.eof())
            {
              block.decode(loadFileDat);
              height++;
              block.setHeightBlock(height);
              spyCBlockRPC::WrapperInformations wrapper;
              wrapper.setDelimitator(ConfiguratorSingleton::getInstance().getDelimitatorLinkInformations());
              block.toTransactionsGraph(saveBlkToJson, wrapper);
            }
            chrono::milliseconds end = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            milliseconds duration = (end - start);
            LOG(ERROR) << "Block readed in " + to_string((duration.count() * milliseconds::period::num / milliseconds::period::den)) + " second";
            saveBlkToJson.close();
            return true;
          }
          LOG(ERROR) << "The file " + inputPath + " not opened";
          throw DAOException("The file " + inputPath + " not opened");

      }
      LOG(ERROR) << "The file input is a directory" << inputPath;
      throw DAOException("The file input is a directory " + inputPath);
  }
  LOG(ERROR) << "The file input not exist" << inputPath;
  throw DAOException("The file input not exist " + inputPath);
}
