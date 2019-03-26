//
// Created by https://github.com/vincenzopalazzo on 2/7/19.
//

#include <fstream>
#include <iostream>
#include <glog/logging.h>
#include "SpyCBlock.h"
#include "../structure/block/block.h"
#include "../persistence/IDAOBlockchain.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"

using namespace spyCBlock;

void SpyCBlock::read(string pathBlockchain) {
    //ifstream *stream = new ifstream(pathBlockchain);

    //ofstream *outStream = new ofstream("test/file_test/first_block_deserialize.txt");

    IDAOBlockchain *dao = new DAOBlockchain();
    vector<Block> blocks;
    cout << "init Parsing on: " << pathBlockchain;
    try {
        blocks = dao->loadBlocks(pathBlockchain);
    } catch (DAOException daoe) {
        LOG(ERROR) << "Exception obtained: " << daoe.what();
    }

    LOG(WARNING) << "Total block readed: " << blocks.size();
    cout << "Finisch parsing, total block readed: " << blocks.size();
}
