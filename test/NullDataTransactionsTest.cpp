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

#include "../structure/block/block.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"
#include "../core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
 * This battery of tests was developed for the testing of a bug,
 * in the alpha version of the parser the Null data transactions had not been taken into account,
 * with this battery of tests the fix that fixes this bug was introduced.
 *
 * The alpha version of this project reports a big problem in memory allocation
 * and therefore this leads to a subsequent rewrite of the way in which data
 * structures are used and how memory is allocated, so as to decrease the workload on processor and RAM
 *
 * @author https://github.com/vincenzopalazzo
 */

vector<unique_ptr<Block>> blocks;
vector<string> previusBlockHashWhitScriptNull;
vector<string> previusBlockHashWhitScriptNullCompare;

//Test for block blk00032
//The error transaction is https://www.blockchain.com/it/btc/tx/c78854360663aa585b0400df7297afc458521bf858e6c93b34d4ca696ae30f29
TEST(NullDataTransactionTest, testNullDataTransaction) {
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("testNullDataTransaction.log").c_str());

    unique_ptr<IDAOBlockchain> dao(new DAOBlockchain());

    try {
        string path = pathMockRoot + "bitcoin/block/bug/blk32";
        blocks = dao->loadBlocks(path);
        ASSERT_EQ(blocks.size(), 915);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//Test for block blk00032
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_equal_to_two) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";
    string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";

    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append(nameFileLog).c_str());

    bool findValueSerched = false;


    ofstream saveFileWhitScriptNull(pathMockRoot + ("previus_hash_script_null_blk32.txt"));
    if(!saveFileWhitScriptNull.is_open())
    {
      LOG(ERROR) << "File not open into path " << pathMockRoot;
      FAIL()<< "File not open into path " << pathMockRoot;
    }

    for(auto &block : blocks)
    {
      for(auto &rawTransaction : block->getRawTransactions())
      {
          for(auto &inputTransaction : rawTransaction->getTxInd())
          {
             if(inputTransaction->getScript().getRawScriptString().empty())
             {
               LOG(WARNING) << "NullDataTransaction findend, the row script is " << inputTransaction->getScript().getRawScriptString();
               findValueSerched = true;
               saveFileWhitScriptNull << rawTransaction->getHashRawTransaction() << endl;
             }
          }

         for(auto &outputTransaction : rawTransaction->getTxOut())
         {
            if(outputTransaction->getScript().getRawScriptString().empty())
            {
              LOG(WARNING) << "NullDataTransaction findend, the row script is " << outputTransaction->getScript().getRawScriptString();
              findValueSerched = true;
              saveFileWhitScriptNull << rawTransaction->getHashRawTransaction() << endl;
            }
         }

      }
    }
    saveFileWhitScriptNull.close();
    ASSERT_TRUE(findValueSerched);
}

//Test for block blk00032
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_load_hash_pb_whit_script_null)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";
  string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
  google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append(nameFileLog).c_str());

  bool findValueSerched = false;


  ifstream saveFileWhitScriptNull(pathMockRoot + "previus_hash_script_null_blk32.txt");
  if(!saveFileWhitScriptNull.is_open())
  {
    LOG(ERROR) << "File not open into path " << pathMockRoot;
    FAIL() << "File not open into path " << pathMockRoot;
  }

  previusBlockHashWhitScriptNull.clear();
  previusBlockHashWhitScriptNullCompare.clear();

  while(!saveFileWhitScriptNull.eof())
  {
    string attualValue;
    saveFileWhitScriptNull >> attualValue;
    if(attualValue.empty())
    {
        continue;
    }
    previusBlockHashWhitScriptNull.push_back(attualValue);
  }

  saveFileWhitScriptNull.close();

  ifstream loadFileReadedToPython(pathMockRoot + "previusHashTheScriptNull_blk32.txt");
  if(!loadFileReadedToPython.is_open())
  {
    LOG(ERROR) << "File not open into path " << pathMockRoot;
    FAIL() << "File not open into path " << pathMockRoot;
  }

  while(!loadFileReadedToPython.eof())
  {
    string attualValue;
    loadFileReadedToPython >> attualValue;
    if(attualValue.empty())
    {
        continue;
    }
    previusBlockHashWhitScriptNullCompare.push_back(attualValue);
  }

  loadFileReadedToPython.close();

  EXPECT_EQ(previusBlockHashWhitScriptNull.size(), previusBlockHashWhitScriptNullCompare.size());

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

    unique_ptr<IDAOBlockchain> dao(new DAOBlockchain());

    try {
        string path = pathMockRoot + "bitcoin/block/bug/blk53";
        blocks = dao->loadBlocks(path);
        ASSERT_EQ(blocks.size(), 751);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//Test for block blk00053
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_equal_to_two_blk53)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";
    string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;

    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append(nameFileLog).c_str());

    bool findValueSerched = false;


    previusBlockHashWhitScriptNull.clear();
    previusBlockHashWhitScriptNullCompare.clear();

    ofstream saveFileWhitScriptNull(pathMockRoot + ("previus_hash_script_null_blk53.txt"));
    if(!saveFileWhitScriptNull.is_open())
    {
      LOG(ERROR) << "File not open into path " << pathMockRoot;
      FAIL() << "File not open into path " << pathMockRoot;
    }

    for(auto &block : blocks)
    {
      for(auto &rawTransaction : block->getRawTransactions())
      {
          for(auto &inputTransaction : rawTransaction->getTxInd())
          {
             if(inputTransaction->getScript().getRawScriptString().empty())
             {
               LOG(WARNING) << "NullDataTransaction findend, the row script is " << inputTransaction->getScript().getRawScriptString();
               findValueSerched = true;
               saveFileWhitScriptNull << rawTransaction->getHashRawTransaction() << endl;
             }
          }

         for(auto &outputTransaction : rawTransaction->getTxOut())
         {
            if(outputTransaction->getScript().getRawScriptString().empty())
            {
              LOG(WARNING) << "NullDataTransaction findend, the row script is " << outputTransaction->getScript().getRawScriptString();
              findValueSerched = true;
              saveFileWhitScriptNull << rawTransaction->getHashRawTransaction() << endl;
            }
         }

      }
    }
    saveFileWhitScriptNull.close();
    ASSERT_TRUE(findValueSerched);
}

//Test for block blk00053
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_load_hash_pb_whit_script_null_blk53)
{

  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
  google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append(nameFileLog).c_str());

  bool findValueSerched = false;


  previusBlockHashWhitScriptNull.clear();
  previusBlockHashWhitScriptNullCompare.clear();

  ifstream saveFileWhitScriptNull(pathMockRoot + ("previus_hash_script_null_blk53.txt"));
  if(!saveFileWhitScriptNull.is_open())
  {
    LOG(ERROR) << "File not open into path " << pathMockRoot;
    FAIL() << "File not open into path " << pathMockRoot;
  }

  while(!saveFileWhitScriptNull.eof())
  {
    string attualValue;
    saveFileWhitScriptNull >> attualValue;
    if(attualValue.empty() || attualValue == "")
    {
        continue;
    }
    previusBlockHashWhitScriptNull.push_back(attualValue);
  }

  saveFileWhitScriptNull.close();

  ifstream loadFileReadedToPython(pathMockRoot + "previusHashTheScriptNull_blk53.txt");
  if(!loadFileReadedToPython.is_open())
  {
    LOG(ERROR) << "File not open into path " << pathMockRoot;
    FAIL() << "File not open into path " << pathMockRoot;;
  }

  while(!loadFileReadedToPython.eof())
  {
    string attualValue;
    loadFileReadedToPython >> attualValue;
    if(attualValue.empty() || attualValue == "")
    {
        continue;
    }
    previusBlockHashWhitScriptNullCompare.push_back(attualValue);
  }

  loadFileReadedToPython.close();

  EXPECT_EQ(previusBlockHashWhitScriptNull.size(), previusBlockHashWhitScriptNullCompare.size());

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

    unique_ptr<IDAOBlockchain> dao(new DAOBlockchain());

    try {
        string path = pathMockRoot + ("bitcoin/block/bug/blk54");
        blocks = dao->loadBlocks(path);
        ASSERT_EQ(blocks.size(), 811);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

//Test for block blk00054
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_equal_to_two_blk54)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append(nameFileLog).c_str());

    bool findValueSerched = false;


    previusBlockHashWhitScriptNull.clear();
    previusBlockHashWhitScriptNullCompare.clear();

    ofstream saveFileWhitScriptNull(pathMockRoot + ("previus_hash_script_null_blk54.txt"));
    if(!saveFileWhitScriptNull.is_open())
    {
      LOG(ERROR) << "File not open into path " << pathMockRoot;
      FAIL();
    }

    for(auto &block : blocks)
    {
      for(auto &rawTransaction : block->getRawTransactions())
      {
          for(auto &inputTransaction : rawTransaction->getTxInd())
          {
             if(inputTransaction->getScript().getRawScriptString().empty())
             {
               LOG(WARNING) << "NullDataTransaction findend, the row script is " << inputTransaction->getScript().getRawScriptString();
               findValueSerched = true;
               saveFileWhitScriptNull << rawTransaction->getHashRawTransaction() << endl;
             }
          }

         for(auto &outputTransaction : rawTransaction->getTxOut())
         {
            if(outputTransaction->getScript().getRawScriptString().empty())
            {
              LOG(WARNING) << "NullDataTransaction findend, the row script is " << outputTransaction->getScript().getRawScriptString();
              findValueSerched = true;
              saveFileWhitScriptNull << rawTransaction->getHashRawTransaction() << endl;
            }
         }

      }
    }
    saveFileWhitScriptNull.close();
    ASSERT_TRUE(findValueSerched);
}

//Test for block blk00054
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_load_hash_pb_whit_script_null_blk54)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";
  string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
  google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append(nameFileLog).c_str());

  bool findValueSerched = false;


  previusBlockHashWhitScriptNull.clear();
  previusBlockHashWhitScriptNullCompare.clear();

  ifstream saveFileWhitScriptNull(pathMockRoot + ("previus_hash_script_null_blk54.txt"));
  if(!saveFileWhitScriptNull.is_open())
  {
    LOG(ERROR) << "File not open into path " << pathMockRoot;
    FAIL() << "File not open into path " << pathMockRoot;
  }

  while(!saveFileWhitScriptNull.eof())
  {
    string attualValue;
    saveFileWhitScriptNull >> attualValue;
    if(attualValue.empty() || attualValue == "")
    {
        continue;
    }
    previusBlockHashWhitScriptNull.push_back(attualValue);
  }

  saveFileWhitScriptNull.close();

  ifstream loadFileReadedToPython(pathMockRoot + ("previusHashTheScriptNull_blk54.txt"));
  if(!loadFileReadedToPython.is_open())
  {
    LOG(ERROR) << "File not open into path " << pathMockRoot;
    FAIL() << "File not open into path " << pathMockRoot;
  }

  while(!loadFileReadedToPython.eof())
  {
    string attualValue;
    loadFileReadedToPython >> attualValue;
    if(attualValue.empty() || attualValue == "")
    {
        continue;
    }
    previusBlockHashWhitScriptNullCompare.push_back(attualValue);
  }

  loadFileReadedToPython.close();

  EXPECT_EQ(previusBlockHashWhitScriptNull.size(), previusBlockHashWhitScriptNullCompare.size());

}



