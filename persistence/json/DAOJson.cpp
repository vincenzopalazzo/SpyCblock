#include <experimental/filesystem>

#include <glog/logging.h>

#include "DAOJson.h"
#include "../DAOException.h"

using namespace spyCBlock;
namespace fs = std::experimental::filesystem;

vector<unique_ptr<Block>> spyCBlock::DAOJson::loadBlocks(string &path)
{
  //do nothig

}

bool DAOJson::saveBlock(string inputPath, string outputPath)
{
  if(inputPath.empty() || outputPath.empty())
  {
    LOG(FATAL) << "Error, the input method are null";
    throw exception();
  }

  if (fs::exists(inputPath))
  {
      if(!fs::is_directory(inputPath))
      {

          ifstream loadFileDat(inputPath);
          if(loadFileDat.is_open())
          {
            vector<unique_ptr<Block>> blockFileBlk;
            while(!loadFileDat.eof())
            {
              auto block = make_unique<Block>();
              block->decode(loadFileDat);
              blockFileBlk.push_back(move(block));
            }
            convertToJson(blockFileBlk, outputPath);
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

void DAOJson::convertToJson(vector<unique_ptr<Block>> &blocks, string outputPath)
{
  if(blocks.empty())
  {
    LOG(ERROR) << "The input velue is null";
    throw DAOException("The input value is null");
  }

  json jsonFileDatConverted;

  json appendrJsonBlock;

  for(auto &block : blocks)
  {
    appendrJsonBlock.push_back(block->toJsonFat());
  }

  jsonFileDatConverted["blocks"] = appendrJsonBlock;

  ofstream saveBlkToJson(outputPath);
  if(saveBlkToJson.is_open())
  {
     saveBlkToJson << jsonFileDatConverted;
     return;
  }
  LOG(ERROR) << "The file output not open " + outputPath;
  throw DAOException("The file output not open " + outputPath);
  return;
}
