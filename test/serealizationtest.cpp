/**
 * @author https://github.com/vincenzopalazzo
 */
#include <gtest/gtest.h>
#include <glog/logging.h>
#include "../persistence/serializationutil.h"
#include "../util/strencodings.h"
#include "../structure/block/block.h"

using namespace spyCBlock;
using namespace std;

TEST(serealization_test, serealization_util_test_uint32)
{
  FLAGS_minloglevel = 0;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serealization_util_test_uint32.log");

  uint32_t nonce = 2083236893;
  //The conversion nonce use a big endian
  string nonceConversion = SerializationUtilSingleton::getInstance()->toSerealizeForm(nonce);
  ASSERT_EQ(nonceConversion, "7c2bac1d");
}

TEST(serealization_test, serealization_util_test_uint)
{
  FLAGS_minloglevel = 0;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serealization_util_test_uint16.log");

  int32_t version = 1;
  /*int32_t versionConverted = htole32(version);
  stringstream stream;
  stream.write((char*) &versionConverted, 4);*/

  //The conversion nonce use a lite endian
  string nonceConversion = SerializationUtilSingleton::getInstance()->toSerealizeForm(version);
  ASSERT_EQ(nonceConversion, "01000000");
}

TEST(serealization_test, serealization_util_test_to_read_file)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serealization_util_test_uint16.log");

  Block *block = new Block();

  std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
  block->decode(fileOut);
  fileOut.close();

  string lietEndiaConversionVersion = SerializationUtilSingleton::getInstance()->toSerealizeForm(block->getBlockHeader().getVersion()); //Is lite endian
  string lietEndiaConversionTimeStamp = SerializationUtilSingleton::getInstance()->toSerealizeForm(block->getBlockHeader().getTime()); // is big endian
  string lietEndiaConversionNbit = SerializationUtilSingleton::getInstance()->toSerealizeForm(block->getBlockHeader().getNBits());
  string lietEndiaConversionNonce = SerializationUtilSingleton::getInstance()->toSerealizeForm(block->getBlockHeader().getNonce());
  string lietEndiaConversionNumTxIn = SerializationUtilSingleton::getInstance()->toSerealizeForm(block->getRawTransactions().at(0).getNumberTxIn());
  string lietEndiaConversionNumTxOut = SerializationUtilSingleton::getInstance()->toSerealizeForm(block->getRawTransactions().at(0).getNumberTxOut());
  string lietEndiaConversionNumScriptLenghtTxIn = SerializationUtilSingleton::getInstance()->toSerealizeForm(
        block->getRawTransactions().at(0).getTxInd().at(0).getScript().getScriptLenght());
  string lietEndiaConversionNumScriptLenghtTxOut = SerializationUtilSingleton::getInstance()->toSerealizeForm(
        block->getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght());

  EXPECT_EQ(lietEndiaConversionVersion, "01000000");
  EXPECT_EQ(lietEndiaConversionTimeStamp, "495fab29");
  EXPECT_EQ(lietEndiaConversionNbit, "1d00ffff");
  EXPECT_EQ(lietEndiaConversionNonce, "7c2bac1d");
  EXPECT_EQ(lietEndiaConversionNumTxIn, "01000000");
  EXPECT_EQ(lietEndiaConversionNumTxOut, "010");
  EXPECT_EQ(lietEndiaConversionNumScriptLenghtTxIn, "4d");
  EXPECT_EQ(lietEndiaConversionNumScriptLenghtTxOut, "43");
}
