/*
 * MIT License
 *
 * Copyright (c) 2019 Vincenzo Palazzo vincenzopalazzodev@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>
#include <utility>

#include "../structure/block/block.h"
#include "../persistence/json/DAOBlkToJson.h"
#include "../persistence/DAOException.h"
#include "../core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
  * Test battery developed to test the DAO for reading all the blk files and
  * the conversion to json of all the corresponding deserialized blk.
  * For more information on DAOBlkToJson, look at the source file DAOBlkToJson.h and .cpp
  *
  * The writing of this DAO shows a big problem of the first version of this parser,
  * that is the irresponsible allocation of the memory of the heap,
  * in fact for the alpha version a new DAOJson has been developed for the resolution of this problem.
  * We bet in the beta version to deprecate DAOJson and to use this DAO
  * because all the memory allocation will be reviewed inside the parser
  *
  * The alpha version of this project reports a big problem in memory allocation and therefore this leads to a
  * subsequent rewrite of the way in which data structures are used and how memory is allocated,
  * so as to decrease the workload on processor and RAM
  *
  * @author https://github.com/vincenzopalazzo
  *
  */

//Fist test for using DAOBlkToJson into all directory bitcoin blocks not exception
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    try {
        bool result = daoBlockchain->saveBlock(pathMockRoot + "bitcoin/block/", pathMockRoot + "bitcoin/blockJson/");
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//Fist test for using DAOBlkToJson into all directory bitcoin blocks with error reading
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data_error_one)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_error_one.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    bool result = daoBlockchain->saveBlock(pathMockRoot + ("bitcoin/"), pathMockRoot + ("bitcoin/blockJson/"));
    ASSERT_FALSE(result); // are inclusind left block in the file blk
}

//Second test for using DAOBlkToJson into all directory bitcoin blocks with error reading
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data_error_two)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_error_two.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    EXPECT_ANY_THROW(daoBlockchain->saveBlock(pathMockRoot + ("bitcoin/block/blk00000.dat"), pathMockRoot + ("bitcoin/blockJson/")));
}

//Third test for using DAOBlkToJson into all directory bitcoin blocks with error reading
TEST(DAOBlkToJsonTest, test_dao_blk_to_json_blockchain_give_file_data_error_null)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_error_null.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOFileBlkJson());
    EXPECT_ANY_THROW(daoBlockchain->saveBlock("", pathMockRoot + ("bitcoin/blockJson/")));
}

