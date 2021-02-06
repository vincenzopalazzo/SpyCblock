// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <gtest/gtest.h>

#include <utility>

#include "../src/core/ConfiguratorSingleton.h"
#include "../src/persistence/DAOException.h"
#include "../src/persistence/json/DAOJson.h"
#include "../src/structure/block/Block.h"

using namespace std;
using namespace spyCBlock;

/**
 * Test battery developed to test the DAO for reading all the blk files and
 * the conversion to json of all the corresponding deserialized blk.
 * For more information on DAoJson, look at the source file DAoJson.h and .cpp
 *
 * The alpha version of this project reports a big problem in memory allocation
 * and therefore this leads to a subsequent rewrite of the way in which data
 * structures are used and how memory is allocated, so as to decrease the
 * workload on processor and RAM
 *
 * @author https://github.com/vincenzopalazzo
 *
 */

// First test for decode all files blk into bitcoin diretory blocks
TEST(DAOJsonTest,
     test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00000) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR,
                            pathLogRoot
                                .append("test_dao_blk_to_json_blockchain_give_"
                                        "file_data_dao_json_test_blk00000.log")
                                .c_str());

  DAOJson dao;
  try {
    bool result =
        dao.saveBlock(pathMockRoot + "bitcoin/block/blk00000.dat",
                      pathMockRoot + "bitcoin/blockJson/blk00000.json");
    ASSERT_TRUE(result);  // are inclusind left block in the file blk
  } catch (DAOException exception) {
    FAIL() << "Test fail for this cause" << exception.what();
  }
}

// TOD initi another test blk00975
TEST(DAOJsonTest,
     test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00975) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR,
                            pathLogRoot
                                .append("test_dao_blk_to_json_blockchain_give_"
                                        "file_data_dao_json_test_blk00975.log")
                                .c_str());

  DAOJson dao;
  try {
    bool result = dao.saveBlock(
        pathMockRoot + "bitcoin/block/serialization_test/blk00975.dat",
        pathMockRoot + "bitcoin/blockJson/blk00975.json");
    ASSERT_TRUE(result);  // are inclusind left block in the file blk
  } catch (DAOException exception) {
    FAIL() << "Test fail for this cause" << exception.what();
  }
}

// for block blk00974
TEST(DAOJsonTest,
     test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00974) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR,
                            pathLogRoot
                                .append("test_dao_blk_to_json_blockchain_give_"
                                        "file_data_dao_json_test_blk00974.log")
                                .c_str());

  DAOJson dao;
  try {
    bool result = dao.saveBlock(
        pathMockRoot + "bitcoin/block/serialization_test/blk00974.dat",
        pathMockRoot + "bitcoin/blockJson/blk00974.json");
    ASSERT_TRUE(result);  // are inclusind left block in the file blk
  } catch (DAOException exception) {
    FAIL() << "Test fail for this cause" << exception.what();
  }
}

// for block blk00032
TEST(DAOJsonTest,
     test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00032) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR,
                            pathLogRoot
                                .append("test_dao_blk_to_json_blockchain_give_"
                                        "file_data_dao_json_test_blk00032.log")
                                .c_str());

  DAOJson dao;
  try {
    bool result = dao.saveBlock(
        pathMockRoot + "bitcoin/block/serialization_test/blk00032.dat",
        pathMockRoot + "bitcoin/blockJson/blk00032.json");
    ASSERT_TRUE(result);  // are inclusind left block in the file blk
  } catch (DAOException exception) {
    FAIL() << "Test fail for this cause" << exception.what();
  }
}

// for block blk00053
TEST(DAOJsonTest,
     test_dao_blk_to_json_blockchain_give_file_data_dao_json_test_blk00053) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR,
                            pathLogRoot
                                .append("test_dao_blk_to_json_blockchain_give_"
                                        "file_data_dao_json_test_blk00053.log")
                                .c_str());

  DAOJson dao;
  try {
    bool result = dao.saveBlock(
        pathMockRoot + "bitcoin/block/serialization_test/blk00053.dat",
        pathMockRoot + "bitcoin/blockJson/blk00053.json");
    ASSERT_TRUE(result);  // are inclusind left block in the file blk
  } catch (DAOException exception) {
    FAIL() << "Test fail for this cause" << exception.what();
  }
}
