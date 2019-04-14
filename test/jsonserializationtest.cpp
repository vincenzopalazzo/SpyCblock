/**
 * @author https://github.com/vincenzopalazzo
 */
#include <gtest/gtest.h>
#include <glog/logging.h>
#include <nlohmann/json.hpp>

#include "../structure/block/block.h"

using namespace spyCBlock;
using namespace nlohmann;

TEST(JsonSerializationTest, serialization_blockheader_test_one)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serialization_blockheader_test_one.log");

  std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");

  Block *block = new Block();

  block->decode(fileOut);
  fileOut.close();

  BlockHeader blockHeader = block->getBlockHeader();
  json jsonBlockheader = blockHeader.toJoson();

  ofstream fileJson("/home/vincenzo/Github/SpyCblock/test/file_test/block_header.json");
  fileJson << jsonBlockheader;

  fileJson.close();
  delete block;

  json toFileJson;
  ifstream getFilejeson("/home/vincenzo/Github/SpyCblock/test/file_test/block_header.json");
  LOG_IF(ERROR, !getFilejeson.is_open()) << "File json not open";

  getFilejeson >> toFileJson;
  getFilejeson.close();

  int version = toFileJson.at("version");
  EXPECT_EQ(1, version);
  string hexPreviusHashBlock = toFileJson.at("previusBlockHeaderHash");
  string markleRoot = toFileJson.at("markleRoot");
  uint32_t time = toFileJson.at("time");
  uint32_t nBits = toFileJson.at("nBits");
  uint32_t nonce = toFileJson.at("nonce");
  EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000", hexPreviusHashBlock);
  EXPECT_EQ("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b", markleRoot);
  EXPECT_EQ(1231006505, time);
  EXPECT_EQ(486604799, nBits);
  EXPECT_EQ(2083236893, nonce);
}

TEST(JsonSerializationTest, serialization_lite_block_test_one)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serialization_blockheader_test_one.log");

  std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");

  Block *block = new Block();

  block->decode(fileOut);
  fileOut.close();


  json JsonBlockLite = block->toJsonLite();

  ofstream fileJson("/home/vincenzo/Github/SpyCblock/test/file_test/block_lite.json");
  fileJson << JsonBlockLite;
  fileJson.close();
  delete block;

  json toFileJson;
  ifstream getFilejeson("/home/vincenzo/Github/SpyCblock/test/file_test/block_lite.json");
  LOG_IF(ERROR, !getFilejeson.is_open()) << "File json not open";

  getFilejeson >> toFileJson;
  getFilejeson.close();

  int magicNumbar = toFileJson.at("magicNumbar");
  int32_t blockSize = toFileJson.at("blockSize");
  EXPECT_EQ(spyCBlock::typeBlock::NETWORK_MAIN, magicNumbar);
  EXPECT_EQ(285 , blockSize);

}

TEST(JsonSerializationTest, serialization_fat_block_test_one)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/serialization_fat_block_test_one.log");

  std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");

  Block *block = new Block();

  block->decode(fileOut);
  fileOut.close();


  json jsonBlockFat = block->toJsonFat();

  ofstream fileJson("/home/vincenzo/Github/SpyCblock/test/file_test/block_fat.json");
  fileJson << jsonBlockFat;

  fileJson.close();
  delete block;



  json toFileJson;
  ifstream getFilejeson("/home/vincenzo/Github/SpyCblock/test/file_test/block_fat.json");
  LOG_IF(ERROR, !getFilejeson.is_open()) << "File json not open";

  getFilejeson >> toFileJson;
  getFilejeson.close();

  int magicNumbar = toFileJson.at("magicNumbar");
  int32_t blockSize = toFileJson.at("blockSize");
  uint64_t numTransactionRaw = toFileJson.at("numbarRawTransactions");
  string hashBlock = toFileJson.at("hashBlock");

  EXPECT_EQ(spyCBlock::typeBlock::NETWORK_MAIN, magicNumbar);
  EXPECT_EQ(285 , blockSize);
  EXPECT_EQ(1, numTransactionRaw);
  EXPECT_EQ(hashBlock, "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");

}

//ADDING TEST FOR SERIALIZATION TRANSACTION
