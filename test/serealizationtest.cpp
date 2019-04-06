/**
 * @author https://github.com/vincenzopalazzo
 */
#include <gtest/gtest.h>
#include <glog/logging.h>
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
  ASSERT_EQ(nonceConversion, "1dac2b7c");
}

TEST(serealization_test, serealization_util_test_uint)
{
  FLAGS_minloglevel = 0;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serealization_util_test_uint16.log");

  int32_t version = 1;
  //The conversion nonce use a lite endian
  string nonceConversion = SerializationUtilSingleton::getInstance()->toSerealizeForm(version);
  ASSERT_EQ(nonceConversion, "01000000");
}

TEST(serealization_test, serealization_util_test_to_read_file)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serealization_util_test_to_read_file.log");

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
  EXPECT_EQ(lietEndiaConversionTimeStamp, "29ab5f49");
  EXPECT_EQ(lietEndiaConversionNbit, "ffff001d");
  EXPECT_EQ(lietEndiaConversionNonce, "1dac2b7c");
  EXPECT_EQ(lietEndiaConversionNumTxIn, "01");
  EXPECT_EQ(lietEndiaConversionNumTxOut, "01");
  EXPECT_EQ(lietEndiaConversionNumScriptLenghtTxIn, "4d");
  EXPECT_EQ(lietEndiaConversionNumScriptLenghtTxOut, "43");
}

TEST(serealization_test, serealization_genesi_block_test_to_read_file)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serealization_block_test_to_read_file.log");

  Block *block = new Block();

  std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
  block->decode(fileOut);
  fileOut.close();

  string serealizationFormBlock = block->toSerealizationForm();
  string attendForm = "0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c";
  transform(attendForm.begin(), attendForm.end(), attendForm.begin(), ::tolower);
  ASSERT_EQ(serealizationFormBlock, attendForm);
}

TEST(serealization_test, serealization_transaction_genesi_block_test_to_read_file)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serealization_transaction_genesi_block_test_to_read_file.log");

  Block *block = new Block();

  std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
  block->decode(fileOut);
  fileOut.close();

  RawTransaction rawTransaction = block->getRawTransactions().at(0);
  string  serealizationFormTransaction = rawTransaction.toSerealizationForm();
  string attendForm = "01000000010000000000000000000000000000000000000000000000000000000000000000FFFFFFFF4D04FFFF001D0104455468652054696D65732030332F4A616E2F32303039204368616E63656C6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F757420666F722062616E6B73FFFFFFFF0100F2052A01000000434104678AFDB0FE5548271967F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4F35504E51EC112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC00000000";
  transform(attendForm.begin(), attendForm.end(), attendForm.begin(), ::tolower);
  ASSERT_EQ(serealizationFormTransaction, attendForm);
}
