//
// Created by https://github.com/vincenzopalazzo on 3/9/19.
//

#include <gtest/gtest.h>
#include <utility>

#include "../structure/block/block.h"
#include "../persistence/json/DAOBlkToJson.h"
#include "../persistence/DAOException.h"

using namespace std;
using namespace spyCBlock;

/*Test directory bitcoin core ok*/
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blk_to_json_blockchain_give_file_data.log");

    //IDAOBlockchain *daoBlockchain = new DAOFileBlkJson();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    try {
        bool result = daoBlockchain->saveBlock("/home/vincenzo/tmp/bitcoin/block/", "/home/vincenzo/tmp/bitcoin/blockJson/");
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

/*Test bitcoin core not ok*/
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data_error_one) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blk_to_json_blockchain_give_file_data_error_one.log");

    //IDAOBlockchain *daoBlockchain = new DAOFileBlkJson();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    bool result = daoBlockchain->saveBlock("/home/vincenzo/tmp/bitcoin/", "/home/vincenzo/tmp/bitcoin/blockJson/");
    ASSERT_FALSE(result); // are inclusind left block in the file blk
}

/*Test bitcoin core not ok*/
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data_error_two) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blk_to_json_blockchain_give_file_data_error_two.log");

    //IDAOBlockchain *daoBlockchain = new DAOFileBlkJson();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    EXPECT_ANY_THROW(daoBlockchain->saveBlock("/home/vincenzo/tmp/bitcoin/block/blk00000.dat", "/home/vincenzo/tmp/bitcoin/blockJson/"));
}

/*Test bitcoin core null directory*/
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data_error_null) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blk_to_json_blockchain_give_file_data_error_null.log");

    //IDAOBlockchain *daoBlockchain = new DAOFileBlkJson();
    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    EXPECT_ANY_THROW(daoBlockchain->saveBlock("", "/home/vincenzo/tmp/bitcoin/blockJson/"));
}

