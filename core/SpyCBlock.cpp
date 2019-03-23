//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#include <fstream>
#include "SpyCBlock.h"
#include "../structure/block/block.h"

using namespace spyCBlock;

void SpyCBlock::read(string pathBlockchain) {
    ifstream *stream = new ifstream(pathBlockchain);

    ofstream *outStream = new ofstream("test/file_test/first_block_deserialize.txt");

    while (!stream->eof())
    {
        Block *block = new Block();
        block->decode(*stream);
        *outStream << block->toString();
        delete block;

    }
}
