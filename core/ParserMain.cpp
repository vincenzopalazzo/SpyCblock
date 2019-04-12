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
    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = false;
    google::InitGoogleLogging("1");
    google::SetLogDestination(google::GLOG_WARNING, "/home/vincenzo/Github/SpyCblock/log/main_log.log");



    SpyCBlock *spyCBlock = new SpyCBlock();
    spyCBlock->convertBlockchainToJson("/home/vincenzo/tmp/bitcoin/block/", "/home/vincenzo/tmp/bitcoin/blockJson/");
    delete spyCBlock;

    return 0;
}
