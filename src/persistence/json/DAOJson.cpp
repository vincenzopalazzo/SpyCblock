#include <experimental/filesystem>
#include <chrono>

#include <glog/logging.h>

#include "DAOJson.h"
#include "../DAOException.h"

using namespace spyCBlock;
using namespace rapidjson;
using namespace std;
namespace fs = std::experimental::filesystem;
using namespace chrono;

bool DAOJson::saveBlock(string inputPath, string outputPath, int &height)
{
  if(inputPath.empty() || outputPath.empty())
  {
    LOG(WARNING) << "Error, the input argument are empty";
    throw DAOException("Error, the input argument are empty");
  }

  if (fs::exists(inputPath))
  {
      if(!fs::is_directory(inputPath))
      {
          ifstream loadFileDat(inputPath);
          //Update conversion to json
          ofstream saveBlkToJson(outputPath);
          if(!saveBlkToJson.is_open()){
              LOG(ERROR) << "The file output not open " + outputPath;
              throw DAOException("The file output not open in tha path " + outputPath);
          }
          OStreamWrapper streamWrapper(saveBlkToJson);
          Writer<OStreamWrapper> writer(streamWrapper);
          if(loadFileDat.is_open())
          {
            //vector<Block> blockFileBlk;
            writer.StartObject();
            writer.Key("blocks");
            writer.StartArray();
            Block block;
            chrono::milliseconds start = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            while(!loadFileDat.eof())
            {

              block.decode(loadFileDat);
              height++;
              block.setHeightBlock(height);
              //blockFileBlk.emplace_back(block);
              block.toJson(writer);

            }
            chrono::milliseconds end = duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch());
            milliseconds duration = (end - start);
            LOG(ERROR) << "Block readed in " + to_string((duration.count() * milliseconds::period::num / milliseconds::period::den)) + " second";
            //ofstream saveBlkToJson(outputPath);
            //convertToJson(blockFileBlk, saveBlkToJson);
            //convertToJsonRapidJson(blockFileBlk, saveBlkToJson);
            writer.EndArray();
            writer.EndObject();
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

//This methid can be removed because I refactoring the methof saveblock
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