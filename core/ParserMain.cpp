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
    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 1;

    SpyCBlock *spyCBlock = new SpyCBlock();
    spyCBlock->read("/home/vincenzo/tmp/bitcoin/block/blk00450.dat");
    return 0;
}
