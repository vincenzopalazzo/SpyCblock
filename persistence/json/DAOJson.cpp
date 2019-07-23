#include <experimental/filesystem>

#include <glog/logging.h>

#include "DAOJson.h"
#include "../DAOException.h"

using namespace spyCBlock;
using namespace nlohmann;
using namespace rapidjson;
using namespace std;
namespace fs = std::experimental::filesystem;

vector<unique_ptr<Block>> spyCBlock::DAOJson::loadBlocks(string &path){}

bool DAOJson::saveBlock(string inputPath, string outputPath)
{
  if(inputPath.empty() || outputPath.empty())
  {
    LOG(WARNING) << "Error, the input method are null";
    throw DAOException("Error, the input method are null");
  }

  if (fs::exists(inputPath))
  {
      if(!fs::is_directory(inputPath))
      {
          ifstream loadFileDat(inputPath);
          if(loadFileDat.is_open())
          {
            vector<Block> blockFileBlk;
            while(!loadFileDat.eof())
            {
              Block block;
              block.decode(loadFileDat);
              blockFileBlk.emplace_back(block);
            }
            ofstream saveBlkToJson(outputPath);
            //convertToJson(blockFileBlk, saveBlkToJson);
            convertToJsonRapidJson(blockFileBlk, saveBlkToJson);
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

void DAOJson::convertToJson(vector<Block> &blocks, ofstream &outputPath)
{
  if(blocks.empty())
  {
    LOG(ERROR) << "The input velue is empty";
    throw DAOException("The input value is empty");
  }

  json jsonFileDatConverted;

  json appendrJsonBlock;

  for(auto &block : blocks)
  {
    appendrJsonBlock.push_back(block.toJsonFat());
  }

  jsonFileDatConverted["blocks"] = appendrJsonBlock;


  if(outputPath.is_open())
  {
     outputPath << jsonFileDatConverted;
     outputPath.clear();
     return;
  }
  LOG(ERROR) << "The file output not open ";
  throw DAOException("The file output not open in tha path ");
}

void DAOJson::convertToJsonRapidJson(vector<Block> &blocks, ofstream &outputPath)
{
  if(blocks.empty())
  {
    LOG(ERROR) << "The input velue is empty";
    throw DAOException("The input value is empty");
  }

  if(outputPath.is_open())
  {
      OStreamWrapper osw(outputPath);
      Writer<rapidjson::OStreamWrapper> writer(osw);

     // writer.Key("block");
      writer.StartObject();

      writer.Key("blocks");
      writer.StartArray();

      for(Block &block : blocks)
      {
        block.toJson(writer);
      }

      writer.EndArray();
      writer.EndObject();
  }else {
      LOG(ERROR) << "The file output not open ";
      throw DAOException("The file output not open in tha path ");
  }
}

