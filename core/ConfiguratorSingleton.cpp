#include <experimental/filesystem>

#include <glog/logging.h>
#include "../include/PropertiesParser.h"

#include "ConfiguratorSingleton.h"

using namespace spyCBlock;
using namespace std;
using namespace cppproperties;

ConfiguratorSingleton::ConfiguratorSingleton()
{
  string pathConfiguration = getRootPath() + PATH_FILE;
  LOG(INFO) << "Path congiration file is: " << pathConfiguration;
  configuration = PropertiesParser::Read(pathConfiguration);
  obligatoryVariable();
}

string ConfiguratorSingleton::getRootPath()
{
  return experimental::filesystem::current_path();
}

void ConfiguratorSingleton::obligatoryVariable()
{
  LOG(WARNING) << "Init setting variable default SpyCBlock";
  pathBlockDat = configuration.GetProperty(PATH_BLOCK_DAT);
  LOG(WARNING) << "The path of the block bitcoin core is: " << pathBlockDat;
  pathBlockDecode = configuration.GetProperty(PATH_BLOCK_DECODE);
  LOG(WARNING) << "The path of the directory for save the block decode is: " << pathBlockDecode;
  formatFileDecode = configuration.GetProperty(FORMAT_BLOCK_DECODE);
  LOG(WARNING) << "The format of the decode output is: " << formatFileDecode;
}

string ConfiguratorSingleton::getPathFileMockTest()
{
  if(pathFileMockTest.empty())
  {
    pathFileMockTest = configuration.GetProperty(PATH_FILE_MOCK_TEST);
     LOG(WARNING) << "The path file mock for thest is: " << pathFileLog;
  }
  return pathFileMockTest;
}

string ConfiguratorSingleton::getDelimitatorLinkInformations()
{
  return configuration.GetProperty(DELIMITATOR_INFORMATION_LINK);
}

int ConfiguratorSingleton::getStartHeightBlock()
{
  return stoi(configuration.GetProperty(NUMBER_FILE_TO_START));
}

string ConfiguratorSingleton::getPathFileLogTest()
{
  if(pathFileLogTest.empty())
  {
    pathFileLogTest = configuration.GetProperty(PATH_FILE_LOG_TEST);
     LOG(WARNING) << "The path file log for thest is: " << pathFileLog;
  }
  return pathFileLogTest;
}

string ConfiguratorSingleton::getPathFileLog()
{
  if(pathFileLog.empty())
  {
    pathFileLog = configuration.GetProperty(PATH_FILE_LOG);
    LOG(WARNING) << "The path file logger is: " << pathFileLog;
  }
  return pathFileLog;
}



string ConfiguratorSingleton::getFormatFileDecode() const
{
  return formatFileDecode;
}


string ConfiguratorSingleton::getPathBlockDecode() const
{
  return pathBlockDecode;
}

string ConfiguratorSingleton::getPathBlockDat() const
{
  return pathBlockDat;
}


