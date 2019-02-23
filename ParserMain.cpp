//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#include <glog/logging.h>
#include "core/SpyCBlock.h"

using namespace google;
using namespace spyCBlock;

int main(int argc, char* argv[])
{
    SpyCBlock *spyCBlock = new SpyCBlock();
    spyCBlock->read("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    return 0;
}
