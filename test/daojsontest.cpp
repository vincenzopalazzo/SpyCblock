//
// Created by https://github.com/vincenzopalazzo on 3/9/19.
//

#include <gtest/gtest.h>
#include <utility>

#include "../structure/block/block.h"
#include "../persistence/json/DAOJson.h"
#include "../persistence/DAOException.h"

using namespace std;
using namespace spyCBlock;

/*Test directory bitcoin core ok*/
TEST(DAOJsonTest, test_dao_blk_to_json_blockchain_give_file_data_dao_json_test) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blk_to_json_blockchain_give_file_data_dao_json_test.log");

    DAOJson dao;
    try {
        bool result = dao.saveBlock("/home/vincenzo/tmp/bitcoin/block/blk00450.dat", "/home/vincenzo/tmp/bitcoin/blockJson/blk00450.json");
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}
