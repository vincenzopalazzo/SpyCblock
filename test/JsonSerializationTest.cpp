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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <nlohmann/json.hpp>

#include "../core/ConfiguratorSingleton.h"
#include "../structure/block/block.h"

using namespace spyCBlock;
using namespace nlohmann;
using namespace rapidjson;

/**
 * This test battery was written to test the json creation function from a bed
 * block.
 *
 * The alpha version of this project reports a big problem in memory allocation
 * and therefore this leads to a subsequent rewrite of the way in which data
 * structures are used and how memory is allocated, so as to decrease the
 * workload on processor and RAM
 *
 * @author https://github.com/vincenzopalazzo
 */

TEST(JsonSerializationTest, serialization_blockheader_test_one) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serialization_blockheader_test_one.log").c_str());

  std::ifstream fileOut(pathMockRoot + ("bitcoin/block/blk00000.dat"));

  Block *block = new Block();

  block->decode(fileOut);
  fileOut.close();

  BlockHeader blockHeader = block->getBlockHeader();
  json jsonBlockheader = blockHeader.toJoson();

  ofstream fileJson(pathMockRoot + "block_header.json");
  fileJson << jsonBlockheader;

  fileJson.close();
  delete block;

  json toFileJson;
  ifstream getFilejeson(pathMockRoot + "block_header.json");
  if (!getFilejeson.is_open()) {
    LOG(ERROR) << "File json not open";
    FAIL() << "File json not open";
  }

  getFilejeson >> toFileJson;
  getFilejeson.close();

  int version = toFileJson.at("version");
  EXPECT_EQ(1, version);
  string hexPreviusHashBlock = toFileJson.at("previusBlockHeaderHash");
  string markleRoot = toFileJson.at("markleRoot");
  uint32_t time = toFileJson.at("time");
  uint32_t nBits = toFileJson.at("nBits");
  uint32_t nonce = toFileJson.at("nonce");
  EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000",
            hexPreviusHashBlock);
  EXPECT_EQ("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b",
            markleRoot);
  EXPECT_EQ(1231006505, time);
  EXPECT_EQ(486604799, nBits);
  EXPECT_EQ(2083236893, nonce);
}

TEST(JsonSerializationTest, serialization_lite_block_test_one) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serialization_blockheader_test_one.log").c_str());

  std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

  Block *block = new Block();

  block->decode(fileOut);
  fileOut.close();

  json JsonBlockLite = block->toJsonLite();

  ofstream fileJson(pathMockRoot + "block_lite.json");
  fileJson << JsonBlockLite;
  fileJson.close();
  delete block;

  json toFileJson;
  ifstream getFilejeson(pathMockRoot + "block_lite.json");
  if (!getFilejeson.is_open()) {
    LOG(ERROR) << "File json not open";
    FAIL() << "File json not open";
  }

  getFilejeson >> toFileJson;
  getFilejeson.close();

  int magicNumbar = toFileJson.at("magicNumbar");
  int32_t blockSize = toFileJson.at("blockSize");
  EXPECT_EQ(spyCBlock::typeBlock::NETWORK_MAIN, magicNumbar);
  EXPECT_EQ(285, blockSize);
}

TEST(JsonSerializationTest, serialization_fat_block_test_one) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serialization_fat_block_test_one.log").c_str());

  std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

  Block *block = new Block();

  block->decode(fileOut);
  fileOut.close();

  json jsonBlockFat = block->toJsonFat();

  ofstream fileJson(pathMockRoot + "file_test/block_fat.json");
  fileJson << jsonBlockFat;

  fileJson.close();
  delete block;

  json toFileJson;
  ifstream getFilejeson(pathMockRoot + "block_fat.json");
  if (!getFilejeson.is_open()) {
    LOG(ERROR) << "File json not open";
    FAIL() << "File json not open";
  }

  getFilejeson >> toFileJson;
  getFilejeson.close();

  int magicNumbar = toFileJson.at("magicNumbar");
  int32_t blockSize = toFileJson.at("blockSize");
  uint64_t numTransactionRaw = toFileJson.at("numbarRawTransactions");
  string hashBlock = toFileJson.at("hashBlock");

  EXPECT_EQ(spyCBlock::typeBlock::NETWORK_MAIN, magicNumbar);
  EXPECT_EQ(285, blockSize);
  EXPECT_EQ(1, numTransactionRaw);
  EXPECT_EQ(hashBlock,
            "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");
}

TEST(JsonSerializationTest, serialization_rapidjson_block_test_one) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  google::SetLogDestination(
      google::ERROR,
      pathLogRoot.append("serialization_rapidjson_block_test_one.log").c_str());

  std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

  Block block;

  block.decode(fileOut);
  fileOut.close();

  ofstream fileJson(pathMockRoot + "block_rapidjson.json");
  rapidjson::OStreamWrapper osw(fileJson);
  rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);

  block.toJson(writer);

  fileJson.close();

  ifstream fileJsonInput(pathMockRoot + "block_rapidjson.json");
  if (!fileJsonInput.is_open()) {
    FAIL() << "File block_rapidjson not open";
  }

  IStreamWrapper isw{fileJsonInput};

  Document jsonSerialization;
  jsonSerialization.ParseStream(isw);

  EXPECT_TRUE(jsonSerialization.HasMember("magicNumbar"));
  EXPECT_TRUE(jsonSerialization.HasMember("blockSize"));
  EXPECT_TRUE(jsonSerialization.HasMember("numbarRawTransactions"));
  EXPECT_TRUE(jsonSerialization.HasMember("hashBlock"));

  int magicNumbar = jsonSerialization["magicNumbar"].GetInt();
  int32_t blockSize = jsonSerialization["blockSize"].GetInt();
  uint64_t numTransactionRaw =
      jsonSerialization["numbarRawTransactions"].GetUint64();
  string hashBlock = jsonSerialization["hashBlock"].GetString();

  EXPECT_EQ(spyCBlock::typeBlock::NETWORK_MAIN, magicNumbar);
  EXPECT_EQ(285, blockSize);
  EXPECT_EQ(1, numTransactionRaw);
  EXPECT_EQ(hashBlock,
            "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");
}

// ADDING TEST FOR SERIALIZATION TRANSACTION
