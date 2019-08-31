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

#include <utility>

#include <gtest/gtest.h>
#include <glog/logging.h>

#include "../util/strencodings.h"

#include "../structure/block/block.h"
#include "../core/ConfiguratorSingleton.h"

using namespace spyCBlock;
using namespace std;

/**
 * This test battery was developed for the test of the parser function
 * that reports the converted data in serialized form, this function is the cure for the creation of the hash
 *
 * The alpha version of this project reports a big problem in memory allocation and therefore this leads to a
 * subsequent rewrite of the way in which data structures are used and how memory is allocated,
 * so as to decrease the workload on processor and RAM
 *
 * @author https://github.com/vincenzopalazzo
 */

TEST(serealization_test, serealization_util_test_uint32)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_util_test_uint32.log").c_str());

  uint32_t nonce = 2083236893;
  string nonceConversion = SerializationUtil::toSerealizeForm(nonce);

  ASSERT_EQ(nonceConversion, "1dac2b7c");
}

TEST(serealization_test, serealization_util_test_uint)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_util_test_uint16.log").c_str());

  int32_t version = 1;
  string nonceConversion = SerializationUtil::toSerealizeForm(version);

  ASSERT_EQ(nonceConversion, "01000000");
}

TEST(serealization_test, serealization_util_test_to_read_file)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_util_test_to_read_file.log").c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

  block->decode(fileOut);
  fileOut.close();

  string lietEndiaConversionVersion = SerializationUtil::toSerealizeForm(block->getBlockHeader().getVersion());
  string lietEndiaConversionTimeStamp = SerializationUtil::toSerealizeForm(block->getBlockHeader().getTime());
  string lietEndiaConversionNbit = SerializationUtil::toSerealizeForm(block->getBlockHeader().getNBits());
  string lietEndiaConversionNonce = SerializationUtil::toSerealizeForm(block->getBlockHeader().getNonce());
  string lietEndiaConversionNumTxIn = SerializationUtil::toSerealizeForm(block->getRawTransactions().at(0).getNumberTxIn());
  string lietEndiaConversionNumTxOut = SerializationUtil::toSerealizeForm(block->getRawTransactions().at(0).getNumberTxOut());
  string lietEndiaConversionNumScriptLenghtTxIn = SerializationUtil::toSerealizeForm(
        block->getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght());
  string lietEndiaConversionNumScriptLenghtTxOut = SerializationUtil::toSerealizeForm(
        block->getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght());

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

TEST(serealization_test, serealization_genesi_block_test_to_read_file)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_block_test_to_read_file.log").c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

  block->decode(fileOut);
  fileOut.close();

  string serealizationFormBlock = block->toSerealizationForm();
  string attendForm = "0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c";

  delete block.release();

  transform(attendForm.begin(), attendForm.end(), attendForm.begin(), ::tolower);

  ASSERT_EQ(serealizationFormBlock, attendForm);
}

TEST(serealization_test, serealization_transaction_genesi_block_test_to_read_file)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_transaction_genesi_block_test_to_read_file.log").c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

  block->decode(fileOut);
  fileOut.close();

  string  serealizationFormTransaction = block->getRawTransactions().at(0).toSerealizationForm();
  string attendForm = "01000000010000000000000000000000000000000000000000000000000000000000000000FFFFFFFF4D04FFFF001D0104455468652054696D65732030332F4A616E2F32303039204368616E63656C6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F757420666F722062616E6B73FFFFFFFF0100F2052A01000000434104678AFDB0FE5548271967F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4F35504E51EC112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC00000000";
  transform(attendForm.begin(), attendForm.end(), attendForm.begin(), ::tolower);

  delete block.release();

  ASSERT_EQ(serealizationFormTransaction, attendForm);
}
