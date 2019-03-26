//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#include <glog/logging.h>
#include "SpyCBlock.h"

using namespace google;
using namespace spyCBlock;

int main(int argc, char* argv[])
{
    google::InitGoogleLogging(argv[0]);
    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = true;

    SpyCBlock *spyCBlock = new SpyCBlock();
    spyCBlock->read("/home/vincenzo/tmp/bitcoin/block/");
    delete spyCBlock;

    return 0;
}
