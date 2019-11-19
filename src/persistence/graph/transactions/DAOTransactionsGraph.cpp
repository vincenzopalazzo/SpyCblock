// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <experimental/filesystem>
#include <chrono>
#include <type_traits>

#include <glog/logging.h>
#include <zlib.h>
#include "../../../../include/spycblockrpc/src/core/graph/WrapperInformations.h"

#include "DAOTransactionsGraph.h"
#include "../../DAOException.h"
#include "../../../core/ConfiguratorSingleton.h"

using namespace std;
namespace fs = std::experimental::filesystem;
using namespace chrono;

bool spyCBlock::DAOTransactionsGraph::saveBlock(const string &inputPath, const string &outputPath, int &height)
{
  if(inputPath.empty() || outputPath.empty()){
    LOG(ERROR) << "Error, the input argument are empty";
    throw DAOException("Error, the input argument are empty");
  }

  if (fs::exists(inputPath)){
      if(!fs::is_directory(inputPath)){
          ifstream loadFileDat(inputPath);
          ofstream saveBlk(outputPath);  //Can same file? or create an file for file blk?
          if(!saveBlk.is_open()){
              LOG(ERROR) << "The file output not open " + outputPath;
              throw DAOException("The file output not open in tha path " + outputPath);
          }

          if(loadFileDat.is_open()){
            Block block;
            chrono::milliseconds start = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            while(!loadFileDat.eof())
            {
              block.decode(loadFileDat);
              if(height != -1){
                block.setHeightBlock(height);
                height++;
              }
              spyCBlockRPC::WrapperInformations wrapper;
              wrapper.setDelimitator(ConfiguratorSingleton::getInstance().getDelimitatorLinkInformations());
              block.toTransactionsGraph(saveBlk, wrapper);
              wrapper.clean(spyCBlockRPC::WrapperInformations::TypeInsert::BLOCK);
            }
            chrono::milliseconds end = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            milliseconds duration = (end - start);
            LOG(ERROR) << "Block readed in " + to_string((duration.count() * milliseconds::period::num / milliseconds::period::den)) + " second";
            saveBlk.close();
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

bool spyCBlock::DAOTransactionsGraph::saveBlockCompress(const string &inputPath, const string &outputPath, int &height)
{
  if(inputPath.empty() || outputPath.empty()){
    LOG(ERROR) << "Error, the input argument are empty";
    throw DAOException("Error, the input argument are empty");
  }

  if (fs::exists(inputPath)){
      if(!fs::is_directory(inputPath)){
          ifstream loadFileDat(inputPath);
          gzFile saveBlk = gzopen(outputPath.c_str(), "wb");

          if(saveBlk == Z_NULL){
              LOG(ERROR) << "The file output not open " + outputPath;
              throw DAOException("The file output not open in tha path " + outputPath);
          }

          if(loadFileDat.is_open()){
            Block block;
            chrono::milliseconds start = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            while(!loadFileDat.eof())
            {
              block.decode(loadFileDat);
              if(height != -1){
                block.setHeightBlock(height);
                height++;
              }
              spyCBlockRPC::WrapperInformations wrapper;
              wrapper.setDelimitator(ConfiguratorSingleton::getInstance().getDelimitatorLinkInformations());
              block.toCompressedTransactionsGraph(saveBlk, wrapper);
            }
            chrono::milliseconds end = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            milliseconds duration = (end - start);
            LOG(ERROR) << "Block readed in " + to_string((duration.count() * milliseconds::period::num / milliseconds::period::den)) + " second";
            gzclose(saveBlk);
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

