#ifndef CONFIGURATORSINGLETON_H
#define CONFIGURATORSINGLETON_H

#include <string>

#include "Properties.h"

using namespace std;
using namespace cppproperties;

namespace spyCBlock {

  class ConfiguratorSingleton
  {
    public:
      static ConfiguratorSingleton& getInstance()
      {
        static ConfiguratorSingleton SINGLETON;

        return SINGLETON;
      }

      string getPathBlockDat() const;

      string getPathBlockDecode() const;

      string getFormatFileDecode() const;

      string getPathFileLog();

      string getPathFileLogTest();

      string getPathFileMockTest();

  private:

      const string PATH_FILE = "/conf.properties";

      const string PATH_BLOCK_DAT = "PATH_BLOCK_DAT";

      const string PATH_BLOCK_DECODE = "PATH_BLOCK_DECODE";

      const string FORMAT_BLOCK_DECODE = "FORMAT_BLOCK_DECODE";

      const string PATH_FILE_LOG = "PATH_FILE_LOG";

      const string PATH_FILE_LOG_TEST = "PATH_FILE_LOG_TEST";

      const string PATH_FILE_MOCK_TEST = "PATH_FILE_MOCK_TEST";

      ConfiguratorSingleton();

      Properties configuration;

      string getRootPath();

      void obligatoryVariable();

      //Variable proprieties obligatory
      string pathBlockDat;

      string pathBlockDecode;

      string formatFileDecode;

      string pathFileLog;

      string pathFileLogTest;

      string pathFileMockTest;

  };

}

#endif // CONFIGURATORSINGLETON_H
