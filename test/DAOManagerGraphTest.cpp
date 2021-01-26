// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt


#include <gtest/gtest.h>
#include <utility>

#include <bitcoinapi/bitcoinapi.h>
#include <bitcoinapi/exception.h>

#include "../src/structure/block/Block.h"
#include "../src/persistence/graph/DAOManagerGraph.h"
#include "../src/persistence/graph/transactions/DAOTransactionsGraph.h"
#include "../src/persistence/DAOException.h"
#include "../src/persistence/graph/DAOManagerGraph.h"
#include "../src/core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
  * TODO refactoring name
  * @author https://github.com/vincenzopalazzo
  *
  */

//Transaction Graph
TEST(DAOManagerGraphTest, test_dao_blk_to_graph_transaction__test_with_blk00000)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_graph_transaction__test_with_blk00000.log").c_str());

    DAOTransactionsGraph dao;
    bool result = false;
    try
    {
      result = dao.saveBlock(pathMockRoot + "bitcoin/block/blk00000.dat", pathMockRoot + "bitcoin/blockGraphtx/blk00000_tx.txt");
    } catch (DAOException ex) {
      FAIL() << "Test falied because was do exception generated, the caused is: " << ex.what();
    }catch(BitcoinException btcEx){
       FAIL() << "Test falied because was do exception generated, the caused is: " << btcEx.getMessage();
    }

    ASSERT_EQ(result, true);

}

//Transaction Graph
TEST(DAOManagerGraphTest, test_dao_blk_to_graph_transaction__test_with_blk00032)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_graph_transaction__test_with_blk00032.log").c_str());

    DAOTransactionsGraph dao;
    bool result = false;
    try
    {
      result = dao.saveBlock(pathMockRoot + "bitcoin/block/bug/blk32/blk00032.dat", pathMockRoot + "bitcoin/blockGraphtx/blk00032_tx.txt");
    } catch (DAOException ex) {
      FAIL() << "Test falied because was do exception generated, the caused is: " << ex.what();
    }catch(BitcoinException btcEx){
       FAIL() << "Test falied because was do exception generated, the caused is: " << btcEx.getMessage();
    }

    ASSERT_EQ(result, true);

}
