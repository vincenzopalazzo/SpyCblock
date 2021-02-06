// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "ConfiguratorSingleton.h"

#include <glog/logging.h>

#include <experimental/filesystem>
#include <iostream>

#include "../../include/cpp-properties/include/PropertiesParser.h"
#include "../DefinitionMacro.h"

using namespace spyCBlock;
using namespace std;
using namespace cppproperties;

ConfiguratorSingleton::ConfiguratorSingleton() {
  string pathConfiguration = getRootPath() + PATH_FILE;
  LOG(INFO) << "Path configuration file is: " << pathConfiguration;
  configuration = PropertiesParser::Read(pathConfiguration);
  obligatoryVariable();
}

string ConfiguratorSingleton::getRootPath() {
  return experimental::filesystem::current_path();
}

void ConfiguratorSingleton::obligatoryVariable() {
  LOG(WARNING) << "Init setting variable default SpyCBlock";
  pathBlockDat = configuration.GetProperty(PATH_BLOCK_DAT);
  LOG(WARNING) << "The path of the block bitcoin core is: " << pathBlockDat;
  pathBlockDecode = configuration.GetProperty(PATH_BLOCK_DECODE);
  LOG(WARNING) << "The path of the directory for save the block decode is: "
               << pathBlockDecode;
  formatFileDecode = configuration.GetProperty(FORMAT_BLOCK_DECODE);
  LOG(WARNING) << "The format of the decode output is: " << formatFileDecode;
}

string ConfiguratorSingleton::getPathFileMockTest() {
  if (pathFileMockTest.empty()) {
    pathFileMockTest = configuration.GetProperty(PATH_FILE_MOCK_TEST);
    LOG(WARNING) << "The path file mock for tests is: " << pathFileLog;
  }
  return pathFileMockTest;
}

string ConfiguratorSingleton::getDelimiterLinkInformation() {
  return configuration.GetProperty(DELIMITER_INFORMATION_LINK);
}

int ConfiguratorSingleton::getStartHeightBlock() {
  return stoi(configuration.GetProperty(NUMBER_FILE_TO_START));
}

int ConfiguratorSingleton::getHowManyFileWouldBeRead() {
  if (this->howManyFileWouldBeRead != -100) {
    return this->howManyFileWouldBeRead;
  }
  string value = configuration.GetProperty(HOW_MANY_FILES_WOULD_BE_READ);
  if (value == "all" || value == "ALL") {
    return -1;
  }
  assertf(isNumber(value) == true,
          "The propriety inside the file "
          "HOW_MANY_FILES_WOULD_BE_READ not is valid");
  return stoi(value);
}

bool ConfiguratorSingleton::isParallelExecution() {
  string value = configuration.GetProperty(PARALLEL_EXECUTION);
  assertf(isBoolean(value) == true,
          "The propriety inside the file PARALLEL_EXECUTION not is valid");

  if (value == "TRUE" || value == "true") {
    return true;
  }
  return false;
}

bool ConfiguratorSingleton::isCompressionResult() {
  string value = configuration.GetProperty(COMPRESSION_RESULT);
  assertf(isBoolean(value) == true,
          "The propriety inside the file COMPRESSION_RESULT not is valid");

  if (value == "TRUE" || value == "true") {
    return true;
  }
  return false;
}

int ConfiguratorSingleton::getLevelLog() {
  if (this->levelLog != -1) {
    return this->levelLog;
  }

  string value = configuration.GetProperty(LEVEL_LOG);
  assertf(isNumber(value) == true,
          "The propriety inside the file LEVEL_LOG not is valid");

  int level = stoi(value);
  if (level < 0 || level > 2) {
    cout << "******************** The propriety LEVEL_LOG not is valid, now "
            "the value is 2, only error log";
  }
  this->levelLog = level;
  return this->levelLog;
}

string ConfiguratorSingleton::getPathFileLogTest() {
  if (pathFileLogTest.empty()) {
    pathFileLogTest = configuration.GetProperty(PATH_FILE_LOG_TEST);
    LOG(WARNING) << "The path file log for thest is: " << pathFileLog;
  }
  return pathFileLogTest;
}

string ConfiguratorSingleton::getPathFileLog() {
  if (pathFileLog.empty()) {
    pathFileLog = configuration.GetProperty(PATH_FILE_LOG);
    LOG(WARNING) << "The path file logger is: " << pathFileLog;
  }
  return pathFileLog;
}

string ConfiguratorSingleton::getFormatFileDecode() const {
  return formatFileDecode;
}

string ConfiguratorSingleton::getPathBlockDecode() const {
  return pathBlockDecode;
}

string ConfiguratorSingleton::getPathBlockDat() const { return pathBlockDat; }
