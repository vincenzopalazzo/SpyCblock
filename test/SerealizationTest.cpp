// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <utility>

#include "../src/core/ConfiguratorSingleton.h"
#include "../src/structure/block/Block.h"
#include "../src/util/strencodings.h"

using namespace spyCBlock;
using namespace std;

/**
 * This test battery was developed for the test of the parser function
 * that reports the converted data in serialized form, this function is the cure
 * for the creation of the hash
 *
 * The alpha version of this project reports a big problem in memory allocation
 * and therefore this leads to a subsequent rewrite of the way in which data
 * structures are used and how memory is allocated, so as to decrease the
 * workload on processor and RAM
 *
 * @author https://github.com/vincenzopalazzo
 */

TEST(serealization_test, serealization_util_test_uint32) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serealization_util_test_uint32.log").c_str());

  uint32_t nonce = 2083236893;
  string nonceConversion = SerializationUtil::toSerealizeForm(nonce);

  ASSERT_EQ(nonceConversion, "1dac2b7c");
}

TEST(serealization_test, serealization_util_test_uint) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serealization_util_test_uint16.log").c_str());

  int32_t version = 1;
  string nonceConversion = SerializationUtil::toSerealizeForm(version);

  ASSERT_EQ(nonceConversion, "01000000");
}

TEST(serealization_test, serealization_util_test_to_read_file) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serealization_util_test_to_read_file.log").c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

  block->decode(fileOut);
  fileOut.close();

  string lietEndiaConversionVersion =
      SerializationUtil::toSerealizeForm(block->getBlockHeader().getVersion());
  string lietEndiaConversionTimeStamp =
      SerializationUtil::toSerealizeForm(block->getBlockHeader().getTime());
  string lietEndiaConversionNbit =
      SerializationUtil::toSerealizeForm(block->getBlockHeader().getNBits());
  string lietEndiaConversionNonce =
      SerializationUtil::toSerealizeForm(block->getBlockHeader().getNonce());
  string lietEndiaConversionNumTxIn = SerializationUtil::toSerealizeForm(
      block->getRawTransactions().at(0).getNumberTxIn());
  string lietEndiaConversionNumTxOut = SerializationUtil::toSerealizeForm(
      block->getRawTransactions().at(0).getNumberTxOut());
  string lietEndiaConversionNumScriptLenghtTxIn =
      SerializationUtil::toSerealizeForm(block->getRawTransactions()
                                             .at(0)
                                             .getTxIn()
                                             .at(0)
                                             .getScript()
                                             .getScriptLength());
  string lietEndiaConversionNumScriptLenghtTxOut =
      SerializationUtil::toSerealizeForm(block->getRawTransactions()
                                             .at(0)
                                             .getTxOut()
                                             .at(0)
                                             .getScript()
                                             .getScriptLength());

  delete block.release();

  EXPECT_EQ(lietEndiaConversionVersion, "01000000");
  EXPECT_EQ(lietEndiaConversionTimeStamp, "29ab5f49");
  EXPECT_EQ(lietEndiaConversionNbit, "ffff001d");
  EXPECT_EQ(lietEndiaConversionNonce, "1dac2b7c");
  EXPECT_EQ(lietEndiaConversionNumTxIn, "01");
  EXPECT_EQ(lietEndiaConversionNumTxOut, "01");
  EXPECT_EQ(lietEndiaConversionNumScriptLenghtTxIn, "4d");
  EXPECT_EQ(lietEndiaConversionNumScriptLenghtTxOut, "43");
}

TEST(serealization_test, serealization_genesi_block_test_to_read_file) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serealization_block_test_to_read_file.log").c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

  block->decode(fileOut);
  fileOut.close();

  string serealizationFormBlock = block->toSerealizationForm();
  string attendForm =
      "01000000000000000000000000000000000000000000000000000000"
      "00000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3"
      "888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c";

  delete block.release();

  transform(attendForm.begin(), attendForm.end(), attendForm.begin(),
            ::tolower);

  ASSERT_EQ(serealizationFormBlock, attendForm);
}

TEST(serealization_test,
     serealization_transaction_genesi_block_test_to_read_file) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(
      google::ERROR,
      pathLogRoot
          .append(
              "serealization_transaction_genesi_block_test_to_read_file.log")
          .c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

  block->decode(fileOut);
  fileOut.close();

  string serealizationFormTransaction =
      block->getRawTransactions().at(0).toSerealizationForm();
  string attendForm =
      "010000000100000000000000000000000000000000000000000000000000000000000000"
      "00FFFFFFFF4D04FFFF001D0104455468652054696D65732030332F4A616E2F3230303920"
      "4368616E63656C6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F75"
      "7420666F722062616E6B73FFFFFFFF0100F2052A01000000434104678AFDB0FE55482719"
      "67F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4F35504E51E"
      "C112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC00000000";
  transform(attendForm.begin(), attendForm.end(), attendForm.begin(),
            ::tolower);

  delete block.release();

  ASSERT_EQ(serealizationFormTransaction, attendForm);
}
