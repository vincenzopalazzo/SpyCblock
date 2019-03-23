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
#include "../crypto/DSha256.h"
#include "glog/logging.h"

#include "../util/strencodings.h"
#include "../cryptobitcoin/Sha256.hpp"
#include "../cryptobitcoin/Sha256Hash.hpp"
#include "../cryptobitcoin/Utils.hpp"

#include "../util/uint256.h"

//TODO temponary included
#include "../cryptobitcoin/TestHelper.hpp"

using namespace std;

/*
 * This the for testin a DSha256 with this example
 * https://en.bitcoin.it/wiki/Protocol_documentation#Hashes
 * */
TEST(hash_test, first_test_sha_not_on_bitcoin_protocolo)
{
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_WARNING,  "/home/vincenzo/Github/SpyCblock/test/log/first_test_sha_not_on_bitcoin_protocolo.log");

    string hello = "hello";

    string sha256Hello = spyCBlock::sha256(hello);
    LOG(INFO) << "The string hello converting with sha256: " << sha256Hello;
    ASSERT_EQ(sha256Hello, "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824");
}

/*
 * This the for testin a DSha256 with this example
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
 * This the for testin a DSha256 with this example
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

    /*stringstream streamString;
    streamString << std::hex << shaHash.value;

    string doubleHash256 = streamString.str();*/

    /*char *doubleHashChar = new char[sizeof (shaHash.value)];
    std:memcpy(doubleHashChar, shaHash.value, sizeof(doubleHashChar));
    string doubleHash = string(doubleHashChar);
    */

    LOG(INFO) << "The string hello converting with double sha256: " << shaHash.ToString();
    ASSERT_EQ(shaHash.ToString(), "9595c9df9075148eb06860365df33584b75bff782a510c6cd4883a419833d50");
}

