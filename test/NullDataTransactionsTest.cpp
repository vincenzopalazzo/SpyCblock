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

#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include "../src/structure/block/block.h"
#include "../src/persistence/DAOException.h"
#include "../src/core/ConfiguratorSingleton.h"
#include "util/DAOUtilTest.h"

using namespace std;
using namespace spyCBlock;

/**
 * This battery of tests was developed for the testing of a bug,
 * in the alpha version of the parser the Null data transactions had not been taken into account,
 * with this battery of tests fixes this bugs was introduced.
 *
 * this battery of tests has a problem with the OPT_return operator, for fix, this problem could be introduced
 * the parser of the hex script, but in the version beta, it is not supported.
 *
 * @author https://github.com/vincenzopalazzo
 */

//Test for block blk00032
//The error transaction is https://www.blockchain.com/it/btc/tx/c78854360663aa585b0400df7297afc458521bf858e6c93b34d4ca696ae30f29
TEST(NullDataTransactionTest, testNullDataTransaction) {
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("testNullDataTransaction.log").c_str());

    DAOUtilTest dao;
    vector<Block> blocks;
    try {
        string path = pathMockRoot + "bitcoin/block/bug/blk32";
        blocks = dao.loadBlocks(path);

        //Find opt return
        bool containsScriptNull = false;
        for(Block &block : blocks)
        {
          LOG(INFO) << "The block: " << block.getBlockHeader().getPreviousBlockHeaderHash().GetHex();
          for(RawTransaction rawTx: block.getRawTransactions())
          {
              LOG(INFO) << "The raw tx: " << rawTx.getLockTime();
              for(TransactionInput txInput : rawTx.getTxIn())
              {
                  LOG(INFO) << "The input tx: " << txInput.getOutpoint().getHash().GetHex();
                  if(txInput.isScriptNull())
                  {
                    containsScriptNull = true;
                  }
              }

              for(TransactionOutput txOutput : rawTx.getTxOut())
              {
                 LOG(INFO) << "The output tx: " << txOutput.getNValue();
                 if(txOutput.isScriptNull())
                 {
                   containsScriptNull = true;
                 }
              }
          }
        }

    ASSERT_EQ(blocks.size(), 933);
    ASSERT_TRUE(containsScriptNull);

    }catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }


}

//Test for block blk00053
//The error transaction is https://www.blockchain.com/it/btc/tx/4fb1ee7b2e8121baf400b4a947508b431c39d64e2192059ff482624ba58f01d2
TEST(NullDataTransactionTest, test_null_data_transaction_blk53)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("testNullDataTransaction.log").c_str());

    DAOUtilTest dao;
    vector<Block> blocks;
    try {
        string path = pathMockRoot + "bitcoin/block/bug/blk53";
        blocks = dao.loadBlocks(path);
        ASSERT_EQ(blocks.size(), 756);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

    //Find the opt return script
    bool containsScriptNull = false;
    for(Block &block : blocks)
    {
      for(RawTransaction rawTx: block.getRawTransactions())
      {
          for(TransactionInput txInput : rawTx.getTxIn())
          {
              if(txInput.isScriptNull())
              {
                containsScriptNull = true;
              }
          }

          for(TransactionOutput txOutput : rawTx.getTxOut())
          {
             if(txOutput.isScriptNull())
             {
               containsScriptNull = true;
             }
          }
      }
    }

    ASSERT_TRUE(containsScriptNull);
}

//Test for block blk00054
//The error transaction is https://www.blockchain.com/it/btc/tx/7bd54def72825008b4ca0f4aeff13e6be2c5fe0f23430629a9d484a1ac2a29b8
TEST(NullDataTransactionTest, test_null_data_transaction_blk54)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("testNullDataTransaction.log").c_str());

    DAOUtilTest dao;
    vector<Block> blocks;
    try {
        string path = pathMockRoot + ("bitcoin/block/bug/blk54");
        blocks = dao.loadBlocks(path);
        ASSERT_EQ(blocks.size(), 819);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

    //Find the opt return script
    bool containsScriptNull = false;
    for(Block &block : blocks)
    {
      for(RawTransaction rawTx: block.getRawTransactions())
      {
         for(TransactionInput txInput : rawTx.getTxIn())
         {
             if(txInput.isScriptNull())
             {
               containsScriptNull = true;
             }
         }

         for(TransactionOutput txOutput : rawTx.getTxOut())
         {
            if(txOutput.isScriptNull())
            {
              containsScriptNull = true;
            }
         }
      }
    }

    ASSERT_TRUE(containsScriptNull);
}



