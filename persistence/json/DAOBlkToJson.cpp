#include <iostream>

#include <glog/logging.h>
#include <nlohmann/json.hpp>

#include "DAOBlkToJson.h"
#include "../DAOException.h"

using namespace spyCBlock;
using namespace std;
using json = nlohmann::json;

bool DAOFileBlkJson::saveBlock(string inputPath, string outputPath)
{
  if (inputPath.empty() || outputPath.empty())
  {
      LOG(ERROR) << "The argument function is null";
      throw new DAOException("The argument function loadBlocks from DAOBlockchain is Empity");
  }

  bool result = false;

  if (fs::exists(inputPath))
  {
      if(fs::is_directory(inputPath))
      {
         fs::path pathObject = inputPath;
          LOG(WARNING) << "Path exits and the path is the directory, the path is:  " << inputPath;
          for (auto &p: fs::directory_iterator(pathObject))
          {
              LOG(WARNING) << "The file examinad is: " << p;
              LOG_IF(ERROR, counterBlock < 0) << "The counter block are negative, this is not possible, the attual value is" << counterBlock;
              string nameFile = getNameFile(p);
              vector<Block> *vectorBlockFileBlk = readBlock(p, counterBlock);

              if (vectorBlockFileBlk != nullptr)
              {
                  LOG(INFO) << "I added block readed in this file " << inputPath;
                  result = convertVectorBlockIntoJson(vectorBlockFileBlk, outputPath, nameFile);
                  if(!result)
                  {
                     LOG(ERROR) << "Error into convert vector blocks readed into json file";
                     delete vectorBlockFileBlk;
                     return result;
                  }
              }
              delete vectorBlockFileBlk;
          }
          return result;
      }
      LOG(ERROR) << "The path not is a directory";
      throw DAOException("The path not is a directory");
  }
  LOG(ERROR) << "The path not exist";
  throw DAOException("The path not exist");
}

vector<Block> *DAOFileBlkJson::readBlock(experimental::filesystem::__cxx11::directory_entry entry, int &counterBlock)
{
  if (!isBlockFileBlk(entry))
  {
      LOG(INFO) << "This path not contain a file blk";
      return nullptr;
  }
  ifstream *stream = new ifstream(entry.path());
  if (stream->is_open())
  {
      LOG(INFO) << "File in this path " << entry.path() << " is open";
      vector<Block> *blocksFile = new vector<Block>();
      while (!stream->eof())
      {
          Block *block = new Block();
          block->decode(*stream);
          block->setHeightBlock(counterBlock);
          counterBlock++;
          LOG(WARNING) << "The numbar blocks readed are: " << counterBlock;
          blocksFile->push_back(*block);
          delete block;
      }
      stream->close();
      delete stream;
      LOG(WARNING) << "Readed a " << blocksFile->size() << " files";
      return blocksFile;
  }
  LOG(ERROR) << "File not open";
  throw DAOException("File not open");
}

//TODO refactoring method into IDAOBlockchain becouse thi method are common
/**
 * Wase possible using the API System library for operation on file name,
 * an example https://en.cppreference.com/w/cpp/filesystem/path/extension
 * for check exstension file
 *
 * @brief DAOFileBlkJson::isBlockFileBlk
 * @param entry
 * @return value bool for indiche if the file is an file blkxxxxx.dat
 */
bool DAOFileBlkJson::isBlockFileBlk(experimental::filesystem::__cxx11::directory_entry entry)
{
  string pathFile = entry.path();
  string tmpPathFile(pathFile);
  LOG(INFO) << "The path in string is: " << pathFile;
  string nameFile = tmpPathFile.substr(tmpPathFile.size() - 12, tmpPathFile.size());
  LOG(INFO) << "The name file in path is " << nameFile;
  bool containsBlk = nameFile.find("blk") != string::npos;
  bool containsExstension = nameFile.find(".dat") != string::npos;
  return containsBlk && containsExstension;
}

//TODO ho modoficato questo da stanco, ho metto dei puntatori
//prova aggiungendo anche unique_ptr.
bool DAOFileBlkJson::convertVectorBlockIntoJson(vector<Block> *blockFileBlk, string outputPath, string nameFile)
{
  if(blockFileBlk == nullptr || outputPath.empty() || nameFile.empty())
  {
    LOG(ERROR) << "The imput parameter is null";
    throw DAOException("Input is null");
  }

  json *jsonBlocksFile = new json();//TODO convert vector into json.

  json listBlocksConvert;

  for(int i = 0; i < static_cast<int>(blockFileBlk->size()); i++)
  {
     listBlocksConvert.push_back(blockFileBlk->at(i).toJsonFat());
  }

  *jsonBlocksFile ={"blocks", listBlocksConvert};


  string nameFileJson = outputPath;
  nameFileJson += nameFile;
  nameFileJson += ".json";

  ofstream *streamOutput = new ofstream(nameFileJson);

  if(streamOutput->is_open())
  {
    *streamOutput << jsonBlocksFile;
    streamOutput->close();
    delete streamOutput;
    delete jsonBlocksFile;
    return true;
  }
  delete streamOutput;
  delete jsonBlocksFile;
  LOG(ERROR) << "ERROR the file is not open into this directory " << outputPath;
  return false;
}

string DAOFileBlkJson::getNameFile(experimental::filesystem::__cxx11::directory_entry entry)
{
  string pathFile = entry.path();
  LOG(INFO) << "Path File is " << pathFile;
  string nameFile = pathFile.substr((pathFile.size() - 12), 8);
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
  throw exception();
}

DAOFileBlkJson::DAOFileBlkJson() = default;

DAOFileBlkJson::~DAOFileBlkJson() = default;

vector<Block> DAOFileBlkJson::loadBlocks(string path)
{
  //do nothing for moment
  return vector<Block>();
}
