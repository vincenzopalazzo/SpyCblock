//
// Created by https://github.com/vincenzopalazzo on 3/9/19.
//

#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include "../structure/block/block.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"

using namespace std;
using namespace spyCBlock;

/*Leggo solo una volta i blocchi e poi effettuo operazioni
 * per verificare la legalita delle operazioni
 */

vector<unique_ptr<Block>> blocks;
vector<string> previusBlockHashWhitScriptNull;
vector<string> previusBlockHashWhitScriptNullCompare;

/*Test for block blk00032*/
/*The error transaction is https://www.blockchain.com/it/btc/tx/c78854360663aa585b0400df7297afc458521bf858e6c93b34d4ca696ae30f29*/
TEST(NullDataTransactionTest, testNullDataTransaction) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/testNullDataTransaction.log");

    unique_ptr<IDAOBlockchain> dao(new DAOBlockchain());

    try {
        string path = "/home/vincenzo/tmp/bitcoin/block/bug/blk32";
        blocks = dao->loadBlocks(path);
        ASSERT_EQ(blocks.size(), 915);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

/*Test for block blk00032*/
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_equal_to_two) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    string pathFileLog = "/home/vincenzo/Github/SpyCblock/test/log";
    string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
    google::SetLogDestination(google::GLOG_ERROR, pathFileLog.c_str());

    bool findValueSerched = false;


    string pathSaveData = "/home/vincenzo/Github/SpyCblock/test/file_test/";

    ofstream saveFileWhitScriptNull(pathSaveData + "previus_hash_script_null_blk32.txt");
    LOG_IF(ERROR, !saveFileWhitScriptNull.is_open()) << "File not open into path " << pathSaveData;

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

/*Test for block blk00032*/
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_load_hash_pb_whit_script_null) {
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  string pathFileLog = "/home/vincenzo/Github/SpyCblock/test/log";
  string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
  google::SetLogDestination(google::GLOG_ERROR, pathFileLog.c_str());

  bool findValueSerched = false;


  string pathSaveData = "/home/vincenzo/Github/SpyCblock/test/file_test/";

  ifstream saveFileWhitScriptNull(pathSaveData + "previus_hash_script_null_blk32.txt");
  LOG_IF(ERROR, !saveFileWhitScriptNull.is_open()) << "File not open into path " << pathSaveData;

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

  ifstream loadFileReadedToPython(pathSaveData + "previusHashTheScriptNull_blk32.txt");
  LOG_IF(ERROR, !loadFileReadedToPython.is_open()) << "File not open into path " << pathSaveData;

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

/*Test for block blk00053*/
/*The error transaction is https://www.blockchain.com/it/btc/tx/4fb1ee7b2e8121baf400b4a947508b431c39d64e2192059ff482624ba58f01d2*/
TEST(NullDataTransactionTest, test_null_data_transaction_blk53) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/testNullDataTransaction.log");

    unique_ptr<IDAOBlockchain> dao(new DAOBlockchain());

    try {
        string path = "/home/vincenzo/tmp/bitcoin/block/bug/blk53";
        blocks = dao->loadBlocks(path);
        ASSERT_EQ(blocks.size(), 751);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

/*Test for block blk00053*/
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_equal_to_two_blk53) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    string pathFileLog = "/home/vincenzo/Github/SpyCblock/test/log";
    string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
    google::SetLogDestination(google::GLOG_ERROR, pathFileLog.c_str());

    bool findValueSerched = false;


    previusBlockHashWhitScriptNull.clear();
    previusBlockHashWhitScriptNullCompare.clear();

    string pathSaveData = "/home/vincenzo/Github/SpyCblock/test/file_test/";

    ofstream saveFileWhitScriptNull(pathSaveData + "previus_hash_script_null_blk53.txt");
    LOG_IF(ERROR, !saveFileWhitScriptNull.is_open()) << "File not open into path " << pathSaveData;

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

/*Test for block blk00053*/
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_load_hash_pb_whit_script_null_blk53) {
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  string pathFileLog = "/home/vincenzo/Github/SpyCblock/test/log";
  string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
  google::SetLogDestination(google::GLOG_ERROR, pathFileLog.c_str());

  bool findValueSerched = false;


  string pathSaveData = "/home/vincenzo/Github/SpyCblock/test/file_test/";


  previusBlockHashWhitScriptNull.clear();
  previusBlockHashWhitScriptNullCompare.clear();

  ifstream saveFileWhitScriptNull(pathSaveData + "previus_hash_script_null_blk53.txt");
  LOG_IF(ERROR, !saveFileWhitScriptNull.is_open()) << "File not open into path " << pathSaveData;

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

  ifstream loadFileReadedToPython(pathSaveData + "previusHashTheScriptNull_blk53.txt");
  LOG_IF(ERROR, !loadFileReadedToPython.is_open()) << "File not open into path " << pathSaveData;

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

/*Test for block blk00054*/
/*The error transaction is https://www.blockchain.com/it/btc/tx/7bd54def72825008b4ca0f4aeff13e6be2c5fe0f23430629a9d484a1ac2a29b8*/
TEST(NullDataTransactionTest, test_null_data_transaction_blk54) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/testNullDataTransaction.log");

    unique_ptr<IDAOBlockchain> dao(new DAOBlockchain());

    try {
        string path = "/home/vincenzo/tmp/bitcoin/block/bug/blk54";
        blocks = dao->loadBlocks(path);
        ASSERT_EQ(blocks.size(), 811);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

/*Test for block blk00054*/
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_equal_to_two_blk54) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    string pathFileLog = "/home/vincenzo/Github/SpyCblock/test/log";
    string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
    google::SetLogDestination(google::GLOG_ERROR, pathFileLog.c_str());

    bool findValueSerched = false;


    previusBlockHashWhitScriptNull.clear();
    previusBlockHashWhitScriptNullCompare.clear();

    string pathSaveData = "/home/vincenzo/Github/SpyCblock/test/file_test/";

    ofstream saveFileWhitScriptNull(pathSaveData + "previus_hash_script_null_blk54.txt");
    LOG_IF(ERROR, !saveFileWhitScriptNull.is_open()) << "File not open into path " << pathSaveData;

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

/*Test for block blk00054*/
TEST(NullDataTransactionTest, test_null_data_transaction_script_leght_load_hash_pb_whit_script_null_blk54) {
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  string pathFileLog = "/home/vincenzo/Github/SpyCblock/test/log";
  string nameFileLog = "test_null_data_transaction_script_leght_equal_to_two.log";
  google::SetLogDestination(google::GLOG_ERROR, pathFileLog.c_str());

  bool findValueSerched = false;


  previusBlockHashWhitScriptNull.clear();
  previusBlockHashWhitScriptNullCompare.clear();

  string pathSaveData = "/home/vincenzo/Github/SpyCblock/test/file_test/";

  ifstream saveFileWhitScriptNull(pathSaveData + "previus_hash_script_null_blk54.txt");
  LOG_IF(ERROR, !saveFileWhitScriptNull.is_open()) << "File not open into path " << pathSaveData;

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

  ifstream loadFileReadedToPython(pathSaveData + "previusHashTheScriptNull_blk54.txt");
  LOG_IF(ERROR, !loadFileReadedToPython.is_open()) << "File not open into path " << pathSaveData;

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



