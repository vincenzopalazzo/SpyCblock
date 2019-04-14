//
// Created by https://github.com/vincenzopalazzo on 3/9/19.
//

#include <gtest/gtest.h>
#include <utility>

#include "../structure/block/block.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"

using namespace std;
using namespace spyCBlock;

/*Test directory bitcoin core ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_date.log");

   //s IDAOBlockchain *daoBlockchain = new DAOBlockchain();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    try {
        string path = "/home/vincenzo/tmp/bitcoin/block";
        vector<unique_ptr<Block>> allBlocks = daoBlockchain->loadBlocks(path);
        ASSERT_EQ(120127, allBlocks.size()); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

}

/*Test bitcoin core not ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_error_one) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_data_error_one.log");

    //IDAOBlockchain *daoBlockchain = new DAOBlockchain();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    string path = "/home/vincenzo/tmp/bitcoin/";
    vector<unique_ptr<Block>> allBlocks = daoBlockchain->loadBlocks(path); // TODO dovrebbe lanciare eccezione se è in una directory sbahliata
    ASSERT_EQ(0, allBlocks.size());
}

/*Test bitcoin core not ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_error_two) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_data_error_two.log");

    //IDAOBlockchain *daoBlockchain = new DAOBlockchain();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    string path = "/home/vincenzo/tmp/bitcoin/block/blk00000.dat";
    EXPECT_ANY_THROW(daoBlockchain->loadBlocks(path));
}

/*Test bitcoin core null directory*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_null) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blockchain_give_file_data_null.log");

    //IDAOBlockchain *daoBlockchain = new DAOBlockchain();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    string path = "";
    EXPECT_ANY_THROW(daoBlockchain->loadBlocks(path));
}
