#include <iostream>

#include <glog/logging.h>
#include <nlohmann/json.hpp>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include "DAOBlkToJson.h"
#include "../DAOException.h"

using namespace spyCBlock;
using namespace std;
using json = nlohmann::json;
using namespace rapidjson;


DAOFileBlkJson::DAOFileBlkJson() = default;

DAOFileBlkJson::~DAOFileBlkJson() = default;

bool DAOFileBlkJson::getFinishBlock() const
{
  return finishBlocks;
}

bool DAOFileBlkJson::saveBlock(string inputPath, string outputPath, int &height)
{
  if (inputPath.empty() || outputPath.empty())
  {
      LOG(ERROR) << "The argument function is null";
      throw DAOException("The argument function loadBlocks from DAOBlockchain is Empity");
  }

  bool result = false;

  if (fs::exists(inputPath))
  {
      if(fs::is_directory(inputPath))
      {

          LOG(WARNING) << "Path exits and the path is the directory, the path is:  " << inputPath;
          string pathFile = nameFileSearched(inputPath);
          while(!pathFile.empty())
          {
              LOG(WARNING) << "The file examinad is: " << pathFile;
              LOG_IF(ERROR, counterBlock < 0) << "The counter block are negative, this is not possible, the attual value is" << counterBlock;
              string nameFile = getNameFile(pathFile);
              vector<Block> vectorBlockFileBlk = readBlock(pathFile, counterBlock);

              if (!vectorBlockFileBlk.empty())
              {
                  LOG(INFO) << "I added block readed in this file " << inputPath;
                  result = convertVectorBlockIntoJson(vectorBlockFileBlk, outputPath, nameFile);
                  if(!result)
                  {
                     LOG(ERROR) << "Error into convert vector blocks readed into json file";
                     vectorBlockFileBlk.clear();
                     return result;
                  }
              }
              currentFile++;

              vectorBlockFileBlk.clear();
              pathFile = nameFileSearched(inputPath);
          }
          return result;
      }
      LOG(ERROR) << "The path not is a directory";
      throw DAOException("The path not is a directory");
  }
  LOG(ERROR) << "The path not exist";
  throw DAOException("The path not exist");
}

//Method whitout file sistem library
vector<Block> DAOFileBlkJson::readBlock(string path, int &conuterBlock)
{
  if (!isBlockFileBlk(path))
  {
      LOG(INFO) << "This path not contain a file blk";
      return vector<Block>();
  }
  if(!fs::exists(path)){
      LOG(ERROR) << "File " << path << " not exist";
      return vector<Block>();
  }
  ifstream stream(path);

  if (stream.is_open())
  {
      LOG(INFO) << "File in this path " << path << " is open";

      vector<Block> blocksFile;
      while (!stream.eof())
      {
          Block block;
          block.decode(stream);
          block.setHeightBlock(counterBlock);

          counterBlock++;
          LOG(WARNING) << "The numbar blocks readed are: " << counterBlock;

          blocksFile.emplace_back(block);
      }

      fileBlkReaded++;

      stream.close();
      LOG(WARNING) << "Readed a " << blocksFile.size() << " files";
      return blocksFile;
  }
  LOG(ERROR) << "File not open";
  throw DAOException("File not open");
}

bool DAOFileBlkJson::isBlockFileBlk(string path)
{
  string tmpPathFile(path);
  LOG(INFO) << "The path in string is: " << path;
  string nameFile = tmpPathFile.substr(tmpPathFile.size() - 12, tmpPathFile.size());
  LOG(INFO) << "The name file in path is " << nameFile;
  bool containsBlk = nameFile.find("blk") != string::npos;
  bool containsExstension = nameFile.find(".dat") != string::npos;
  return containsBlk && containsExstension;
}

//TODO ho modoficato questo da stanco, ho metto dei puntatori
//prova aggiungendo anche unique_ptr.
bool DAOFileBlkJson::convertVectorBlockIntoJson(vector<Block> &blockFileBlk, string outputPath, string nameFile)
{
  if(blockFileBlk.empty() || outputPath.empty() || nameFile.empty())
  {
    LOG(ERROR) << "The imput parameter is null";
    throw DAOException("Input is null");
  }
  string nameFileJson = outputPath;
  nameFileJson += nameFile + ".json";

  ofstream streamOutput(nameFileJson);

  if(streamOutput.is_open())
  {
      OStreamWrapper osw(streamOutput);
      Writer<rapidjson::OStreamWrapper> writer(osw);

      writer.StartObject();

      writer.Key("blocks");
      writer.StartArray();

      for(Block block : blockFileBlk)
      {
        block.toJson(writer);
      }

      writer.EndArray();
      writer.EndObject();

      streamOutput.close();
      return true;
  }
  LOG(ERROR) << "ERROR the file is not open into this directory " << outputPath;
  return false;
}

string DAOFileBlkJson::getNameFile(string path)
{
  LOG(INFO) << "Path File is " << path;
  string nameFile = path.substr((path.size() - 12), 8);
  LOG(WARNING) << "Name file analized is " << nameFile << "and creating file json whit this name";
  LOG_IF(ERROR, nameFile.empty()) << "Name file empity";
  return nameFile;
}


string DAOFileBlkJson::nameFileSearched(string pathInput)
{
  if(pathInput.empty())
  {
    LOG(ERROR) << "Input function null";
    throw exception();
  }
  LOG(ERROR) << "Attual value current file blk: " << currentFile;
  //Search file blk.dat
  if(currentFile < 10) //Il path input deve avere per forza il /
  {   //refactoring using a &

     return pathInput + "blk0000" + to_string(currentFile) + ".dat";

  }else if(currentFile < 100)
  {
      return pathInput + "blk000" + to_string(currentFile) + ".dat";
  }else if (currentFile < 1000)
  {
      return pathInput + "blk00" + to_string(currentFile) + ".dat";
  }else if (currentFile < 10000)
  {
      return pathInput + "blk0" + to_string(currentFile) + ".dat";
  }else if (currentFile < 100000) {

      return pathInput + "blk0" + to_string(currentFile) + ".dat";
  }
  LOG(ERROR) << "The current file is greater to 100000, the value current file is:" << currentFile;
  return "";
}

vector<unique_ptr<Block>> DAOFileBlkJson::loadBlocks(string &path)
{
  //do nothing for moment
  return vector<unique_ptr<Block>>();
}
