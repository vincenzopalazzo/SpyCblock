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
#include "glog/logging.h"

#include "../util/strencodings.h"
#include "../cryptobitcoin/Sha256.hpp"
#include "../cryptobitcoin/Sha256Hash.hpp"
#include "../cryptobitcoin/Utils.hpp"
#include "../crypto/utilcrypto.h"

//TODO temponary included
#include "../cryptobitcoin/TestHelper.hpp"

using namespace std;

/*
 * This the for testin a sha256 cryptobitcoinlibrary with this example
 * https://en.bitcoin.it/wiki/Protocol_documentation#Hashes
 * */
TEST(hash_test, first_test_double_sha_not_on_bitcoin_protocolo)
{
    //Init logger
    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_WARNING,  "/home/vincenzo/Github/SpyCblock/test/log/first_test_sha_not_on_bitcoin_protocolo.log");

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

    string version = "01000000";
    string previusBlock = "0000000000000000000000000000000000000000000000000000000000000000";
    string merkleRoot = "3ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a";
    string timeStamp = "29ab5f49";
    string bit = "ffff001d";
    string nonce = "1dac2b7c";

    string numberRawTransactions = "01";
    string versionRawTransaction = version;
    string numbarTransactionInput = "01";
    string output = "0000000000000000000000000000000000000000000000000000000000ffffffff";
    //string anotherCamp2 = "ffffffff";
    string scriptLenght = "4d";
    string scriptSing = "04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73";
    string sequences = "ffffffff";
    string numbarTransactionOutput = "01";
    string cAmmount = "00f2052a01000000";
    string publicKeyScriptLenght = "43";
    string publicKeyScript = "4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac";
    string lockTime = "00000000";
    stringstream stream;
    stream << numberRawTransactions << versionRawTransaction << numbarTransactionInput << output << scriptLenght << scriptSing << sequences << numbarTransactionOutput << cAmmount << publicKeyScriptLenght << publicKeyScript << lockTime;
    //stream  << versionRawTransaction << output << scriptSing << sequences << cAmmount << publicKeyScript << lockTime;


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
    //stream << version << previusBlock << marckleRoot << timeStamp << bit << nonce;
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
    //stream << version << previusBlock << marckleRoot << timeStamp << bit << nonce;
    stream  << version << previusBlock << merkleRoot << timeStamp << bit << nonce;


    //Bytes byte = asciiBytes(stream.str().c_str());
    //Sha256Hash shaHash = Sha256::getDoubleHash(byte.data(), byte.size()); //method one
    //string strin = stream.str().c_str();
    string value = stream.str();
    //char* arrayByte = spyCBlock::UtilCrypto::ToHexIntoByte(value);
    vector<unsigned char> vectorByte = spyCBlock::UtilCrypto::ToHexIntoVectorByte(value);

    Sha256Hash shaHash = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size()); //method two

    LOG(INFO) << "The hash example documantation bitcoin block converting with double sha256: " << shaHash.ToStringForProtocol();
    ASSERT_EQ(shaHash.ToStringForProtocol(), "00000000000000001e8d6829a8a21adc5d38d0a473b144b6765798e61f98bd1d");
    // 6500f13bc254c59e9f3d77bd0b1999e686fadf7765ae2b59266d1d835b869083 //method one
    // 6500f13bc254c59e9f3d77bd0b1999e686fadf7765ae2b59266d1d835b869083 //method two
}

