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
 *
 * @author https://github.com/vincenzopalazzo on 3/9/19.
 */
#include <gtest/gtest.h>
#include <utility>

#include "../structure/block/block.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"
#include "../core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
  * Test battery developed to test the DAO for reading all the blk files for testing.
  * For more information on the DAOBlockchain, look at the source file DAOBlockchain.h and .cpp
  *
  * The alpha version of this project reports a big problem in memory allocation and therefore this leads to a
  * subsequent rewrite of the way in which data structures are used and how memory is allocated,
  * so as to decrease the workload on processor and RAM
  *
  * @author https://github.com/vincenzopalazzo
  *
  */

/*Test directory bitcoin core ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blockchain_give_file_date.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    try {
        string path = pathMockRoot.append("bitcoin/block");
        vector<unique_ptr<Block>> allBlocks = daoBlockchain->loadBlocks(path);
        ASSERT_EQ(120127, allBlocks.size()); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

}

/*Test bitcoin core not ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_error_one)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blockchain_give_file_data_error_one.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    string path = pathMockRoot.append("bitcoin/");
    vector<unique_ptr<Block>> allBlocks = daoBlockchain->loadBlocks(path); // TODO dovrebbe lanciare eccezione se è in una directory sbagliata
    ASSERT_EQ(0, allBlocks.size());
}

/*Test bitcoin core not ok*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_error_two)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blockchain_give_file_data_error_two.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    string path = pathMockRoot.append("bitcoin/block/blk00000.dat");
    EXPECT_ANY_THROW(daoBlockchain->loadBlocks(path));
}

/*Test bitcoin core null directory*/
TEST(DAOBlockchainTest, test_dao_blockchain_give_file_data_null)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blockchain_give_file_data_null.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());
    string path = "";
    EXPECT_ANY_THROW(daoBlockchain->loadBlocks(path));
}
