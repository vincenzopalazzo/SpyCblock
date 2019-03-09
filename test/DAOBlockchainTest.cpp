//
// Created by https://github.com/vincenzopalazzo on 3/9/19.
//

#include <gtest/gtest.h>

#include "../structure/block/block.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"

using namespace std;
using namespace spyCBlock;

/*Test directory bitcoin core ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data) {
    //Init logger
    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_WARNING, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_date.log");

    DAOBlockchain *daoBlockchain = new DAOBlockchain(); //TODO using a interface
    try {
        vector<Block> allBlocks = daoBlockchain->loadBlocks("/home/vincenzo/tmp/bitcoin/block");
        ASSERT_EQ(120127, allBlocks.size()); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

/*Test bitcoin core not ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_error_one) {
    //Init logger
    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_WARNING, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_data_error_one.log");

    DAOBlockchain *daoBlockchain = new DAOBlockchain(); //TODO using a interface
    vector<Block> allBlocks = daoBlockchain->loadBlocks("/home/vincenzo/tmp/bitcoin/"); // TODO dovrebbe lanciare eccezione se è in una directory sbahliata
    ASSERT_EQ(0, allBlocks.size());
}

/*Test bitcoin core not ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_error_two) {
    //Init logger
    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_WARNING, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_data_error_two.log");

    DAOBlockchain *daoBlockchain = new DAOBlockchain(); //TODO using a interface
    EXPECT_ANY_THROW(daoBlockchain->loadBlocks("/home/vincenzo/tmp/bitcoin/block/blk00000.dat"));
}

/*Test bitcoin core null directory*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_null) {
    //Init logger
    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_WARNING, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_data_null.log");

    DAOBlockchain *daoBlockchain = new DAOBlockchain(); //TODO using a interface
    EXPECT_ANY_THROW(daoBlockchain->loadBlocks(""));
}
