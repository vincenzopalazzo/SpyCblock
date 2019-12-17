// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef CONFIGURATORSINGLETON_H
#define CONFIGURATORSINGLETON_H

#include <string>
#include <algorithm>
#include <assert.h>

#include "../../include/cpp-properties/include/Properties.h"

namespace spyCBlock {

  class ConfiguratorSingleton
  {
    public:

      static ConfiguratorSingleton& getInstance()
      {
        static ConfiguratorSingleton SINGLETON;

        return SINGLETON;
      }

      std::string getPathBlockDat() const;

      std::string getPathBlockDecode() const;

      std::string getFormatFileDecode() const;

      std::string getPathFileLog();

      std::string getPathFileLogTest();

      std::string getPathFileMockTest();

      std::string getDelimitatorLinkInformations();

      int getStartHeightBlock();

      //if the value of this propriety is "all" the getter will return -1 value
      int getHowManyFileWouldBeRead();

      bool isParallelExecution();

      bool isCompressionResult();

      //if the value is < 0 and > 2 the catter value result is 2 with an print error value
      int getLevelLog();

  protected:

      ConfiguratorSingleton();

  private:

      const std::string PATH_FILE = "/conf.properties";

      const std::string PATH_BLOCK_DAT = "PATH_BLOCK_DAT";

      const std::string PATH_BLOCK_DECODE = "PATH_BLOCK_DECODE";

      const std::string FORMAT_BLOCK_DECODE = "FORMAT_BLOCK_DECODE";

      const std::string PATH_FILE_LOG = "PATH_FILE_LOG";

      const std::string LEVEL_LOG = "LEVEL_LOG";

      const std::string PATH_FILE_LOG_TEST = "PATH_FILE_LOG_TEST";

      const std::string PATH_FILE_MOCK_TEST = "PATH_FILE_MOCK_TEST";

      const std::string DELIMITATOR_INFORMATION_LINK = "DELIMITATOR_INFORMATION_LINK";

      const std::string NUMBER_FILE_TO_START = "NUMBER_FILE_TO_START";

      const std::string HOW_MANY_FILES_WOULD_BE_READ = "HOW_MANY_FILES_WOULD_BE_READ";

      const std::string PARALEL_EXCECUTION = "PARALEL_EXCECUTION";

      const std::string COMPRESSION_RESULT = "COMPRESSION_RESULT";

      cppproperties::Properties configuration;

      std::string getRootPath();

      void obligatoryVariable();

      //Variable proprieties obligatory
      std::string pathBlockDat;

      std::string pathBlockDecode;

      std::string formatFileDecode;

      std::string pathFileLog;

      std::string pathFileLogTest;

      std::string pathFileMockTest;

      //Variable by default

      int howManyFileWouldBeRead = -100;

      int levelLog = -1;

      inline bool isNumber(const std::string& s)
      {
          return !s.empty() && std::find_if(s.begin(),s.end(), [](char c) {
              return !std::isdigit(c);
            }) == s.end();
      }

      inline bool isBoolean(const std::string& s){
        return ((s == "true" || s == "TRUE") || s == "false" || s == "FALSE");
      }

  };

}

#endif // CONFIGURATORSINGLETON_H
