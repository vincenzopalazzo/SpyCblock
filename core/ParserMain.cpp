//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#include <glog/logging.h>
#include "SpyCBlock.h"

using namespace google;
using namespace spyCBlock;

using namespace std;

int main(int argc, char* argv[])
{
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::InitGoogleLogging("2");
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/log/main_log.log");



    SpyCBlock *spyCBlock = new SpyCBlock();
    spyCBlock->convertBlockchainToJson("/media/vincenzo/VincentHDD/blocks/", "/media/vincenzo/VincentHDD/blockjson/");
    delete spyCBlock;

    return 0;
}
