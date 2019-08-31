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

#include "../src/structure/block/block.h"
#include "../src/persistence/json/DAOJson.h"
#include "../src/persistence/DAOException.h"
#include "../src/core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
  * Test battery developed to test the DAO for reading all the blk files and
  * the conversion to json of all the corresponding deserialized blk.
  * For more information on DAoJson, look at the source file DAoJson.h and .cpp
  *
  * The alpha version of this project reports a big problem in memory allocation and therefore this leads to a
  * subsequent rewrite of the way in which data structures are used and how memory is allocated,
  * so as to decrease the workload on processor and RAM
  *
  * @author https://github.com/vincenzopalazzo
  *
  */

//First test for decode all files blk into bitcoin diretory blocks
TEST(DAOJsonTest, test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00000)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00000.log").c_str());

    DAOJson dao;
    try {
        int height = 0;
        bool result = dao.saveBlock(pathMockRoot + "bitcoin/block/blk00000.dat", pathMockRoot + "bitcoin/blockJson/blk00000.json", height);
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//TOD initi another test blk00975
TEST(DAOJsonTest, test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00975)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00975.log").c_str());

    DAOJson dao;
    try {
        int height = 0;
        bool result = dao.saveBlock(pathMockRoot + "bitcoin/block/serialization_test/blk00975.dat", pathMockRoot + "bitcoin/blockJson/blk00975.json", height);
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//for block blk00974
TEST(DAOJsonTest, test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00974)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00974.log").c_str());

    DAOJson dao;
    try {
        int height = 0;
        bool result = dao.saveBlock(pathMockRoot + "bitcoin/block/serialization_test/blk00974.dat", pathMockRoot + "bitcoin/blockJson/blk00974.json", height);
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//for block blk00032
TEST(DAOJsonTest, test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00032)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00032.log").c_str());

    DAOJson dao;
    try {
        int height = 0;
        bool result = dao.saveBlock(pathMockRoot + "bitcoin/block/serialization_test/blk00032.dat", pathMockRoot + "bitcoin/blockJson/blk00032.json", height);
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//for block blk00053
TEST(DAOJsonTest, test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00053)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00053.log").c_str());

    DAOJson dao;
    try {
        int height = 0;
        bool result = dao.saveBlock(pathMockRoot + "bitcoin/block/serialization_test/blk00053.dat", pathMockRoot + "bitcoin/blockJson/blk00053.json", height);
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}
