//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#include <fstream>
#include <iostream>
#include <glog/logging.h>
#include "SpyCBlock.h"
#include "../structure/block/block.h"
#include "../persistence/IDAOBlockchain.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/json/DAOBlkToJson.h"
#include "../persistence/DAOException.h"
#include "../persistence/json/DAOJson.h"

using namespace spyCBlock;

void SpyCBlock::read(string pathBlockchain) {

  ifstream *stream = new ifstream(pathBlockchain);

  ofstream *outStream = new ofstream("/home/vincenzo/Desktop/deserealize_file/blk00450.txt");

  while (!stream->eof()) {
    Block *block = new Block();
    block->decode(*stream);
    *outStream << block->toString();
    delete block;
    }
}

bool SpyCBlock::convertBlockchainToJson(string locationBitcoinCore, string destinationBitcoinCoreJson)
{
  if(locationBitcoinCore.empty() || destinationBitcoinCoreJson.empty())
  {
    LOG(ERROR) << "The input/s method are/is null";
    throw "Input are null";
  }

  unique_ptr<DAOFileBlkJson> dao(new DAOFileBlkJson);

  bool resultConversion = false;



  resultConversion = dao->saveBlock(locationBitcoinCore, destinationBitcoinCoreJson);




  if(resultConversion)
  {
      cout << "Conversion bitcoin-core into json O.K" << endl;
      return resultConversion;
  }
  cout << "Conversion bitcoin-core into json K.O" << endl;
  return resultConversion;

}

void SpyCBlock::convertBlkIntoJson(string locationBitcoinCore, string destinationBitcoinCoreJson)
{
  if(locationBitcoinCore.empty() || destinationBitcoinCoreJson.empty())
  {
    LOG(ERROR) << "The input argument ar null";
    throw exception();
  }

  string pathInput = nameFileSearched(locationBitcoinCore);

  while(pathInput != "")
  {
    LOG(ERROR) << "Current file blk is " + to_string(currentFile);

    string fileNameOutput = getNameFile(pathInput);
    DAOJson dao;

    destinationBitcoinCoreJson += fileNameOutput;
    dao.saveBlock(pathInput, destinationBitcoinCoreJson);

    currentFile++;
    pathInput = nameFileSearched(locationBitcoinCore);
  }

}

string SpyCBlock::nameFileSearched(string pathInput)
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

string SpyCBlock::getNameFile(string path)
{
  LOG(INFO) << "Path File is " << path;
  string nameFile = path.substr((path.size() - 12), 8);
  LOG(WARNING) << "Name file analized is " << nameFile << "and creating file json whit this name";
  LOG_IF(ERROR, nameFile.empty()) << "Name file empity";
  return nameFile;
}
