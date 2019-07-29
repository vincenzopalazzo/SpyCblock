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

#include <bitset>
#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <string.h>
#include <sstream>

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "../util/strencodings.h"
#include "../cryptobitcoin/Sha256.hpp"
#include "../cryptobitcoin/Sha256Hash.hpp"
#include "../cryptobitcoin/Utils.hpp"
#include "../cryptobitcoin/TestHelper.hpp"

#include "../crypto/UtilCrypto.h"
#include "../structure/block/block.h"
#include "../crypto/CryptoCore.h"
#include "../core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
 * This test battery was developed for testing the parser function that calculates hash according to the bitcoin protocol.
 * The Bitcoin-Cryptography-Library (https://github.com/nayuki/Bitcoin-Cryptography-Library) library is used
 *
 * The alpha version of this project reports a big problem in memory allocation and therefore this leads to a subsequent
 * rewrite of the way in which data structures are used and how memory is allocated, so as to decrease the workload on processor and RAM
 *
 * @author https://github.com/vincenzopalazzo
 */


//This the for testin a sha256 cryptobitcoinlibrary with this example
// https://en.bitcoin.it/wiki/Protocol_documentation#Hashes
TEST(hash_test, first_test_double_sha_not_on_bitcoin_protocol)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR,  pathLogRoot.append("first_test_sha_not_on_bitcoin_protocol.log").c_str());

    string hello = "hello";

    Bytes byte = asciiBytes(hello.c_str());

    Sha256Hash shaHash = Sha256::getHash(byte.data(), byte.size());

    LOG(INFO) << "The string hello converting with sha256: " << shaHash.ToString();

    ASSERT_EQ(shaHash.ToString(), "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824");
}

/*
 * This the for testin a sha256 cryptobitcoinlibrary with this example
 * https://en.bitcoin.it/wiki/Protocol_documentation#Hashes
 * */
TEST(hash_test, first_test_double_sha_not_on_bitcoin_crypolibrary)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR,  pathLogRoot.append("first_test_sha_not_on_bitcoin_protocolo.log").c_str());

    string hello = "hello";

    Bytes byte = asciiBytes(hello.c_str());
    Sha256Hash shaHash = Sha256::getDoubleHash(byte.data(), byte.size());

    LOG(INFO) << "The string hello converting with double sha256: " << shaHash.ToString();
    ASSERT_EQ(shaHash.ToString(), "9595c9df90075148eb06860365df33584b75bff782a510c6cd4883a419833d50");
}

/*
 * The hash bit genesi block
01000000
01
0000000000000000000000000000000000000000000000000000000000000000
FFFFFFFF
4D
04FFFF001D0104455468652054696D65732030332F4A616E2F32303039204368616E63656C6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F757420666F722062616E6B73
FFFFFFFF
01
00F2052A01000000
43
4104678AFDB0FE5548271967F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4F35504E51EC112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC
00000000

//The hash complete "01000000010000000000000000000000000000000000000000000000000000000000000000FFFFFFFF4D04FFFF001D0104455468652054696D65732030332F4A616E2F32303039204368616E63656C6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F757420666F722062616E6B73FFFFFFFF0100F2052A01000000434104678AFDB0FE5548271967F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4F35504E51EC112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC00000000";

*/

TEST(hash_test, first_test_double_sha_bit_genesi_block_transaction_bitcoin_crypolibrary)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR,  pathLogRoot.append("first_test_sha_not_on_bitcoin_protocolo.log").c_str());

    string versionRawTransaction = "01000000";
    string numbarTransactionInput = "01";
    string output = "0000000000000000000000000000000000000000000000000000000000000000ffffffff";
    string scriptLenght = "4d";
    string scriptSing = "04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73";
    string sequences = "ffffffff";
    string numbarTransactionOutput = "01";
    string cAmmount = "00f2052a01000000";
    string publicKeyScriptLenght = "43";
    string publicKeyScript = "4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac";
    string lockTime = "00000000";

    string hexForm = versionRawTransaction;
    hexForm += numbarTransactionInput;
    hexForm += output;
    hexForm += scriptLenght;
    hexForm += scriptSing;
    hexForm += sequences;
    hexForm += numbarTransactionOutput;
    hexForm += cAmmount;
    hexForm += publicKeyScriptLenght;
    hexForm += publicKeyScript;
    hexForm += lockTime;;

    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(hexForm);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

    LOG(INFO) << "The hash genesi transactions converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b");

}

TEST(hash_test, first_test_double_sha_bit_genesi_block_bitcoin_crypolibrary)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR,  pathLogRoot.append("first_test_sha_not_on_bitcoin_protocolo.log").c_str());

    string version = "01000000";
    string previusBlock = "0000000000000000000000000000000000000000000000000000000000000000";
    string merkleRoot = "3ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a";
    string timeStamp = "29ab5f49";
    string bit = "ffff001d";
    string nonce = "1dac2b7c";

    string hexForm = version;
    hexForm += previusBlock;
    hexForm += merkleRoot;
    hexForm += timeStamp;
    hexForm += bit;
    hexForm += nonce;

    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(hexForm);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

    LOG(INFO) << "The hash genesi block converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");
}

/**
  * The test with this data example protocol bitcoin documentation
  * https://en.bitcoin.it/wiki/Block_hashing_algorithm
  * @author https://github.com/vincenzopalazzo
 */

TEST(hash_test, first_test_double_sha_bit_esample_block_bitcoin_crypolibrary)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR,  pathLogRoot.append("first_test_double_sha_bit_esample_block_bitcoin_crypolibrary.log").c_str());

    string version = "01000000";
    string previusBlock = "81cd02ab7e569e8bcd9317e2fe99f2de44d49ab2b8851ba4a308000000000000";
    string merkleRoot = "e320b6c2fffc8d750423db8b1eb942ae710e951ed797f7affc8892b0f1fc122b";
    string timeStamp = "c7f5d74d";
    string bit = "f2b9441a";
    string nonce = "42a14695";

    string hexForm = version;
    hexForm += previusBlock;
    hexForm += merkleRoot;
    hexForm += timeStamp;
    hexForm +=bit;
    hexForm += nonce;

    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(hexForm);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

    LOG(INFO) << "The hash example documantation bitcoin block converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "00000000000000001e8d6829a8a21adc5d38d0a473b144b6765798e61f98bd1d");
    // 6500f13bc254c59e9f3d77bd0b1999e686fadf7765ae2b59266d1d835b869083
}

/*
  Test the value readed with parser
*/
TEST(hash_test, first_test_comparable_value_readed)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, pathLogRoot.append("first_test_comparable_value_readed.log").c_str());

    unique_ptr<Block> block(new Block());

    std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

    block->decode(fileOut);
    fileOut.close();

    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getVersion()), "01000000");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getPreviousBlockHeaderHash()), "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getMerkleRoot()), "3ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getTime()), "29ab5f49");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getNBits()), "ffff001d");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getNonce()), "1dac2b7c");

}

TEST(hash_test, first_test_comparable_hash_value_readed)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, pathLogRoot.append("unserialize_block_test.log").c_str());

    unique_ptr<Block> block(new Block());

    std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

    block->decode(fileOut);
    fileOut.close();

    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getVersion()), "01000000");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getPreviousBlockHeaderHash()), "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getMerkleRoot()), "3ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getTime()), "29ab5f49");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getNBits()), "ffff001d");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block->getBlockHeader().getNonce()), "1dac2b7c");

    string hexForm = SerializationUtil::toSerealizeForm(block->getBlockHeader().getVersion());
    hexForm += SerializationUtil::toSerealizeForm(block->getBlockHeader().getPreviousBlockHeaderHash());
    hexForm += SerializationUtil::toSerealizeForm(block->getBlockHeader().getMerkleRoot());
    hexForm += SerializationUtil::toSerealizeForm(block->getBlockHeader().getTime());
    hexForm += SerializationUtil::toSerealizeForm(block->getBlockHeader().getNBits());
    hexForm += SerializationUtil::toSerealizeForm(block->getBlockHeader().getNonce());

    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(hexForm);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

    LOG(INFO) << "The hash example documantation bitcoin block converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");

}

TEST(hash_test, first_test_comparable_transaction_value_readed)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, pathLogRoot.append("first_test_comparable_value_readed.log").c_str());

    Block block;

    std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

    block.decode(fileOut);
    fileOut.close();

    //RawTransaction raw = block->getRawTransactions().at(0);

    string version = to_string(block.getRawTransactions().at(0).getVersion());

    EXPECT_EQ(SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getVersion()), "01000000");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getNumberTxIn()), "01");
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex(),
              "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(
                block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN()), "ffffffff");

    EXPECT_EQ(SerializationUtil::toSerealizeForm(
                block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght()), "4d");
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getScript().getRawScriptString(),
              "04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxIn().at(0).getSequences()), "ffffffff");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getNumberTxOut()), "01");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxOut().at(0).getNValue()), "00f2052a01000000");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght()), "43");
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().at(0)
                   .getScript().getRawScriptString().substr(0, block.getRawTransactions().at(0).getTxOut().at(0)
                                                                     .getScript().getScriptLenght().getValue() * 2),
              "4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac");
    EXPECT_EQ(SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getLockTime()), "00000000");
}

TEST(hash_test, first_test_comparable_transaction_hash_value_readed)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, pathLogRoot.append("first_test_comparable_value_readed.log").c_str());

    Block block;

    std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

    block.decode(fileOut);
    fileOut.close();


    string hexForm = SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getVersion());
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getNumberTxIn());
    hexForm += block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex();
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN());
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght());
    hexForm += block.getRawTransactions().at(0).getTxIn().at(0)
                    .getScript().getRawScriptString().substr(0, block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght().getValue() * 2);
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxIn().at(0).getSequences());
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getNumberTxOut());
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxOut().at(0).getNValue());
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght());
    hexForm += block.getRawTransactions().at(0).getTxOut().at(0)
                    .getScript().getRawScriptString().substr(0, block.getRawTransactions().at(0).getTxOut().at(0)
                                                                      .getScript().getScriptLenght().getValue() * 2);
    hexForm += SerializationUtil::toSerealizeForm(block.getRawTransactions().at(0).getLockTime());

    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(hexForm);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

    LOG(INFO) << "The hash genesi transactions converting with double sha256: " << shaHash.ToStringForProtocol();
    EXPECT_EQ(shaHash.ToStringForProtocol(), "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b");
}

TEST(hash_test, hash_block_genesi_test_to_read_file)
{
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_block_test_to_read_file.log").c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

  block->decode(fileOut);
  fileOut.close();

  string serealizationFormBlock = block->toSerealizationForm();
  vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(serealizationFormBlock);

  Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

  string expectedHash = "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f";

  ASSERT_EQ(shaHash.ToStringForProtocol(), expectedHash);
}

TEST(hash_test, hash_transaction_genesi_block_test_to_read_file)
{
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("hash_transaction_genesi_block_test_to_read_file.log").c_str());

  Block block;

  ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

  block.decode(fileOut);
  fileOut.close();

  string serealizationFormTransaction = block.getRawTransactions().at(0).toSerealizationForm();

  vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(serealizationFormTransaction);

  Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

  string expectedHash = "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b";

  ASSERT_EQ(shaHash.ToStringForProtocol(), expectedHash);
}

TEST(hash_test, hash_transaction_genesi_block_test_to_read_file_with_scriptssingleton)
{
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("hash_transaction_genesi_block_test_to_read_file.log").c_str());

  Block block;

  std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");
  block.decode(fileOut);
  fileOut.close();

  string  serealizationFormTransaction = block.getRawTransactions().at(0).toSerealizationForm();

  string gettedHash = CryptoSingleton::getIstance().getHash256(serealizationFormTransaction);

  string expectedHash = "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b";

  ASSERT_EQ(gettedHash, expectedHash);
}

TEST(hash_test, hash_genesi_block_test_to_read_file_with_scriptssingleton)
{
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("hash_transaction_genesi_block_test_to_read_file.log").c_str());

  unique_ptr<Block> block(new Block());

  std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

  block->decode(fileOut);
  fileOut.close();

  string  serealizationFormTransaction = block->toSerealizationForm();

  string gettedHash = CryptoSingleton::getIstance().getHash256(serealizationFormTransaction);

  string expectedHash = "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f";

  ASSERT_EQ(gettedHash, expectedHash);
}

TEST(hash_test, hash_confront_txOut_hash_whit_txInput_hash_contenute_scriptssingleton)
{
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("hash_confront_txOut_hash_whit_txInput_hash_contenute_scriptssingleton.log").c_str());

  std::ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00000.dat"));

  Block block;

  block.decode(fileOut);

  //TransactionInput input = block->getRawTransactions().at(0)->getTxInd().at(0);
  OutPoint outpoint = block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint();
  string hashTxout = outpoint.getHash().GetHex();

  //TransactionOutput output = block->getRawTransactions().at(0).getTxOut().at(0);
  string hexoutput = block.getRawTransactions().at(0).getTxOut().at(0).toSerealizationForm();
  string hashOutput = CryptoSingleton::getIstance().getHash256(hexoutput);

  ASSERT_EQ(hashTxout, hashTxout);
}

/*
 * https://www.blockchain.com/it/btc/block/000000000000000001c984a6589be98fd3c593a1d707a7fdaaa4adf748632022
 * @brief TEST
 */

TEST(hash_test, hash_calculate_hash_block_whit_fat_raw_transaction_scriptssingleton)
{
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("hash_calculate_hash_block_whit_fat_raw_transaction_scriptssingleton.log").c_str());

  ifstream fileOut(pathMockRoot.append("bitcoin/block/blk00450.dat"));

  unique_ptr<Block> block(new Block());

  block->decode(fileOut);

  string hexBlock = block->toSerealizationForm();
  string hashBlock = CryptoSingleton::getIstance().getHash256(hexBlock);

  string expettedHashBlock = "000000000000000001c984a6589be98fd3c593a1d707a7fdaaa4adf748632022";

  //RawTransaction rawTransaction = block->getRawTransactions().at(0);
  string hexRawTransaction = block->getRawTransactions().at(0).toSerealizationForm();
  string heshRawTransaction = CryptoSingleton::getIstance().getHash256(hexRawTransaction);

  string expettedHash = "f2a140b42b47c649a30823712dc568e25443ed390168c897ed5baa52cc50cc4a";


  //RawTransaction rawTransactionMoreInput = block->getRawTransactions().at(3);
  string hexRawTransactionMoreInput = block->getRawTransactions().at(3).toSerealizationForm();
  string heshRawTransactionMoreInput = CryptoSingleton::getIstance().getHash256(hexRawTransactionMoreInput);

  string expettedHashMoreInput = "8bbcf573e66cba09f3109a2eca0589a09232caad248b58ae69cc24bb1a22b264";

  EXPECT_EQ(2461, block->getRawTransactions().size());
  ASSERT_EQ(hashBlock, expettedHashBlock);
  ASSERT_EQ(heshRawTransaction, expettedHash);
  ASSERT_EQ(heshRawTransaction, expettedHash);
}

