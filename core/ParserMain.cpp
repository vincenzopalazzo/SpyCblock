//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#include <glog/logging.h>

#include "SpyCBlock.h"
#include "ConfiguratorSingleton.h"

using namespace google;
using namespace spyCBlock;

using namespace std;

int main(int argc, char* argv[])
{
  //TODO configuration logger to the ConfiguratorSingleton
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::InitGoogleLogging("2");
    string pathLogFile = ConfiguratorSingleton::getInstance().getPathFileLog() + "/main_log.log";
    google::SetLogDestination(google::GLOG_ERROR, pathLogFile.c_str());

    SpyCBlock spyCBlock = SpyCBlock();

    //TODO fix the bug id The path contains the end /
    spyCBlock.convertBlkIntoJson(ConfiguratorSingleton::getInstance().getPathBlockDat() + "/", ConfiguratorSingleton::getInstance().getPathBlockDecode() + "/");

    return 0;
}
