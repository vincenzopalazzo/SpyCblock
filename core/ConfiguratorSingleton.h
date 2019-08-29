#ifndef CONFIGURATORSINGLETON_H
#define CONFIGURATORSINGLETON_H

#include <string>

#include "../include/Properties.h"

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

  protected:
      ConfiguratorSingleton();

  private:

      const std::string PATH_FILE = "/conf.properties";

      const std::string PATH_BLOCK_DAT = "PATH_BLOCK_DAT";

      const std::string PATH_BLOCK_DECODE = "PATH_BLOCK_DECODE";

      const std::string FORMAT_BLOCK_DECODE = "FORMAT_BLOCK_DECODE";

      const std::string PATH_FILE_LOG = "PATH_FILE_LOG";

      const std::string PATH_FILE_LOG_TEST = "PATH_FILE_LOG_TEST";

      const std::string PATH_FILE_MOCK_TEST = "PATH_FILE_MOCK_TEST";

      const std::string DELIMITATOR_INFORMATION_LINK = "DELIMITATOR_INFORMATION_LINK";

      const std::string NUMBER_FILE_TO_START = "NUMBER_FILE_TO_START";

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

  };

}

#endif // CONFIGURATORSINGLETON_H
