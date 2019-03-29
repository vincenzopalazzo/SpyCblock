//
// Created by https://github.com/vincenzopalazzo on 3/23/19.
//

#include <gtest/gtest.h>
#include <bitset>
#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <string.h>
#include <sstream>
#include "glog/logging.h"

#include "../util/strencodings.h"
#include "../cryptobitcoin/Sha256.hpp"
#include "../cryptobitcoin/Sha256Hash.hpp"
#include "../cryptobitcoin/Utils.hpp"
#include "../crypto/utilcrypto.h"
#include "../structure/block/block.h"

//Includinf dfor convert string into hash byte
//this is library for bitcoin crittografy library
#include "../cryptobitcoin/TestHelper.hpp"

using namespace std;
using namespace spyCBlock;

/*
 * This the for testin a sha256 cryptobitcoinlibrary with this example
 * https://en.bitcoin.it/wiki/Protocol_documentation#Hashes
 * */
TEST(hash_test, first_test_double_sha_not_on_bitcoin_protocol)
{
    //Init logger
    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_WARNING,  "/home/vincenzo/Github/SpyCblock/test/log/first_test_sha_not_on_bitcoin_protocol.log");

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
    //Init logger
    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_WARNING,  "/home/vincenzo/Github/SpyCblock/test/log/first_test_sha_not_on_bitcoin_protocolo.log");

    string hello = "hello";

    Bytes byte = asciiBytes(hello.c_str());
    Sha256Hash shaHash = Sha256::getDoubleHash(byte.data(), byte.size());

    LOG(INFO) << "The string hello converting with double sha256: " << shaHash.ToString();
    ASSERT_EQ(shaHash.ToString(), "9595c9df90075148eb06860365df33584b75bff782a510c6cd4883a419833d50");
}

/*
 * The hash bit genesi block block
01000000
01000000
0000000000000000000000000000000000000000000000000000000000
FFFFFFFF
4D
04FFFF001D0104455468652054696D65732030332F4A616E2F32303039204368616E63656C6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F757420666F722062616E6B73
FFFFFFFF
01
00F2052A01000000
43
4104678AFDB0FE5548271967F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4F35504E51EC112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC
00000000
*/

TEST(hash_test, first_test_double_sha_bit_genesi_block_transaction_bitcoin_crypolibrary)
{
    //Init logger
    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_WARNING,  "/home/vincenzo/Github/SpyCblock/test/log/first_test_sha_not_on_bitcoin_protocolo.log");

    string versionRawTransaction = "01000000";
    string numbarTransactionInput = "01000000";
    string output = "0000000000000000000000000000000000000000000000000000000000ffffffff";
    string scriptLenght = "4d";
    string scriptSing = "04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73";
    string sequences = "ffffffff";
    string numbarTransactionOutput = "01";
    string cAmmount = "00f2052a01000000";
    string publicKeyScriptLenght = "43";
    string publicKeyScript = "4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac";
    string lockTime = "00000000";

    //TODO refactorinf, this is unic method for create a string?
    stringstream stream;

    //The hash complete, font:
    //stream << "01000000010000000000000000000000000000000000000000000000000000000000000000FFFFFFFF4D04FFFF001D0104455468652054696D65732030332F4A616E2F32303039204368616E63656C6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F757420666F722062616E6B73FFFFFFFF0100F2052A01000000434104678AFDB0FE5548271967F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4F35504E51EC112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC00000000";

    //This is correct sequences for create a hash raw transaction
    stream << versionRawTransaction << numbarTransactionInput << output << scriptLenght << scriptSing
           << sequences << numbarTransactionOutput << cAmmount << publicKeyScriptLenght << publicKeyScript << lockTime;
    string waitingString = stream.str();

    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(waitingString);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

    LOG(INFO) << "The hash genesi transactions converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b");

}

TEST(hash_test, first_test_double_sha_bit_genesi_block_bitcoin_crypolibrary)
{
    //Init logger
    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_WARNING,  "/home/vincenzo/Github/SpyCblock/test/log/first_test_sha_not_on_bitcoin_protocolo.log");

    string version = "01000000";
    string previusBlock = "0000000000000000000000000000000000000000000000000000000000000000";
    string merkleRoot = "3ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a";
    string timeStamp = "29ab5f49";
    string bit = "ffff001d";
    string nonce = "1dac2b7c";

    stringstream stream;
    stream  << version << previusBlock << merkleRoot << timeStamp << bit << nonce;

    string waitingString = stream.str();
    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(waitingString);

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
    //Init logger
    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_INFO,  "/home/vincenzo/Github/SpyCblock/test/log/first_test_double_sha_bit_esample_block_bitcoin_crypolibrary.log");

    string version = "01000000";
    string previusBlock = "81cd02ab7e569e8bcd9317e2fe99f2de44d49ab2b8851ba4a308000000000000";
    string merkleRoot = "e320b6c2fffc8d750423db8b1eb942ae710e951ed797f7affc8892b0f1fc122b";
    string timeStamp = "c7f5d74d";
    string bit = "f2b9441a";
    string nonce = "42a14695";

    stringstream stream;
    stream  << version << previusBlock << merkleRoot << timeStamp << bit << nonce;

    string value = stream.str();
    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(value);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size()); //method two

    LOG(INFO) << "The hash example documantation bitcoin block converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "00000000000000001e8d6829a8a21adc5d38d0a473b144b6765798e61f98bd1d");
    // 6500f13bc254c59e9f3d77bd0b1999e686fadf7765ae2b59266d1d835b869083 //method one
    // 6500f13bc254c59e9f3d77bd0b1999e686fadf7765ae2b59266d1d835b869083 //method two
}

/*
Test the value readed with parser
*/
TEST(hash_test, first_test_comparable_value_readed) {
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/first_test_comparable_value_readed.log");

    Block *block = new Block();

    std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    block->decode(fileOut);
    fileOut.close();
    std::stringstream hex_string;
    hex_string << std::hex << block->getMagicNum();
    string version = to_string(block->getBlockHeader().getVersion());
    EXPECT_EQ(version, "01000000");
    EXPECT_EQ(block->getBlockHeader().getPreviousBlockHeaderHash().GetHex(), "81cd02ab7e569e8bcd9317e2fe99f2de44d49ab2b8851ba4a308000000000000");
    EXPECT_EQ(block->getBlockHeader().getMerkleRoot().GetHex(), "e320b6c2fffc8d750423db8b1eb942ae710e951ed797f7affc8892b0f1fc122b");
    EXPECT_EQ(to_string(block->getBlockHeader().getTime()), "c7f5d74d");
    EXPECT_EQ(to_string(block->getBlockHeader().getNBits()), "f2b9441a");
    EXPECT_EQ(to_string(block->getBlockHeader().getNonce()), "42a14695");
}

TEST(hash_test, first_test_comparable_hash_value_readed) {
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/unserialize_block_test.log");

    Block *block = new Block();

    std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    block->decode(fileOut);
    fileOut.close();

    stringstream stream;
    stream  << to_string(block->getBlockHeader().getVersion()) << block->getBlockHeader().getPreviousBlockHeaderHash().GetHex()
            << block->getBlockHeader().getMerkleRoot().GetHex() << to_string(block->getBlockHeader().getTime())
            << to_string(block->getBlockHeader().getNBits()) << to_string(block->getBlockHeader().getNonce());

    string value = stream.str();
    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(value);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size()); //method two

    LOG(INFO) << "The hash example documantation bitcoin block converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "00000000000000001e8d6829a8a21adc5d38d0a473b144b6765798e61f98bd1d");

}

TEST(hash_test, first_test_comparable_transaction_value_readed) {
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/first_test_comparable_value_readed.log");

    Block *block = new Block();

    std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    block->decode(fileOut);
    fileOut.close();

    RawTransaction raw = block->getRawTransactions().at(0);

    string version = to_string(raw.getVersion());
    EXPECT_EQ(version, "01000000");
    EXPECT_EQ(to_string(raw.getNumberTxIn().getValue()), "01000000");
    EXPECT_EQ(raw.getTxInd().at(0).getOutpoint().getHash().GetHex(), "0000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(to_string(raw.getTxInd().at(0).getOutpoint().getN()), "ffffffff");
    EXPECT_EQ(HexStr(to_string(raw.getTxInd().at(0).getScript().getScriptLenght().getValue())), "4d");
    EXPECT_EQ(raw.getTxInd().at(0).getScript().getRawScriptString(), "04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73");
    EXPECT_EQ(to_string(raw.getTxInd().at(0).getSequences()), "ffffffff");
    EXPECT_EQ(to_string(raw.getNumberTxOut().getValue()), "01");
    EXPECT_EQ(HexStr(to_string(raw.getTxOut().at(0).getNValue())), "00f2052a01000000");
    EXPECT_EQ(HexStr(to_string(raw.getTxOut().at(0).getScript().getScriptLenght().getValue())), "43");
    EXPECT_EQ(raw.getTxOut().at(0).getScript().getRawScriptString().substr(0, raw.getTxOut().at(0).getScript().getScriptLenght().getValue() * 2), "4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac");
    EXPECT_EQ(to_string(raw.getLockTime()), "00000000");
}

TEST(hash_test, first_test_comparable_transaction_hash_value_readed) {
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, "/home/vincenzo/Github/spyCblock/test/log/first_test_comparable_value_readed.log");

    Block *block = new Block();

    std::ifstream fileOut("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    block->decode(fileOut);
    fileOut.close();

    RawTransaction raw = block->getRawTransactions().at(0);

    stringstream stream;
    stream << raw.getVersion() << to_string(raw.getNumberTxIn().getValue()) << raw.getTxInd().at(0).getOutpoint().getHash().GetHex() << to_string(raw.getTxInd().at(0).getOutpoint().getN())
           << HexStr(to_string(raw.getTxInd().at(0).getScript().getScriptLenght().getValue())) << to_string(raw.getTxInd().at(0).getSequences()) << to_string(raw.getNumberTxOut().getValue())
           << to_string(raw.getTxOut().at(0).getNValue()) << HexStr(to_string(raw.getTxOut().at(0).getScript().getScriptLenght().getValue()))
           << raw.getTxOut().at(0).getScript().getRawScriptString().substr(0, raw.getTxOut().at(0).getScript().getScriptLenght().getValue() *2) << to_string(raw.getLockTime());

    string waitingString = stream.str();

    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(waitingString);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());

    LOG(INFO) << "The hash genesi transactions converting with double sha256: " << shaHash.ToStringForProtocol();
    EXPECT_EQ(shaHash.ToStringForProtocol(), "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b");
}

