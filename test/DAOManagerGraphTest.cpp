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

#include <bitcoinapi/bitcoinapi.h>
#include <bitcoinapi/exception.h>

#include "../structure/block/block.h"
#include "../persistence/graph/DAOManagerGraph.h"
#include "../persistence/DAOException.h"
#include "../persistence/graph/DAOManagerGraph.h"
#include "../core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
  *
  * @author https://github.com/vincenzopalazzo
  *
  */

//First test for decode all files blk into bitcoin diretory blocks
TEST(DAOManagerGraphTest, test_dao_blk_to_graph_blockchain_give_file_data_dao_json_test_blk00000)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_graph_blockchain_give_file_data_dao_json_test_blk00000.log").c_str());

    DAOManagerGraph dao;
    bool result = false;
    try
    {
      int height = 0;
      result = dao.saveBlock(pathMockRoot + "bitcoin/block/blk00000.dat", pathMockRoot + "bitcoin/blockGraph/blk00000.txt", height);
    } catch (DAOException ex) {
      FAIL() << "Test falied because was do exception generated, the caused is: " << ex.what();
    }catch(BitcoinException btcEx){
       FAIL() << "Test falied because was do exception generated, the caused is: " << btcEx.getMessage();
    }

    ASSERT_EQ(result, true);

}

TEST(DAOManagerGraphTest, test_dao_blk_to_graph_blockchain_give_file_data_dao_json_test_blk00032)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 1;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_dao_blk_to_graph_blockchain_give_file_data_dao_json_test_blk00032.log").c_str());

    DAOManagerGraph dao;
    bool result = false;
    try
    {
      int height = 0;
      result = dao.saveBlock(pathMockRoot + "bitcoin/block/bug/blk32/blk00032.dat", pathMockRoot + "bitcoin/blockGraph/blk00032.txt", height);
    } catch (DAOException ex) {
      FAIL() << "Test falied because was do exception generated, the caused is: " << ex.what();
    }catch(BitcoinException btcEx){
       FAIL() << "Test falied because was do exception generated, the caused is: " << btcEx.getMessage();
    }

    ASSERT_EQ(result, true);

}
