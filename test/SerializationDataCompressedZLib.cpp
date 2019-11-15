// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <utility>
#include <chrono>

#include <gtest/gtest.h>
#include <glog/logging.h>

#include "../src/structure/block/block.h"
#include "../src/core/ConfiguratorSingleton.h"
#include "../src/persistence/graph/transactions/TransactionsRawGraph.h"

using namespace spyCBlock;
using namespace std;
using namespace chrono;

/**
 * TODO add information
 *
 * @author https://github.com/vincenzopalazzo
 */

TEST(serealization_compressed_test, serealization_util_test_no_compression_on_blk00000)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_util_test_no_compression_on_blk00000.log").c_str());

  ifstream readBlock(pathMockRoot + "/bitcoin/block/blk00000.dat");
  ofstream streamCppNotCompressed(pathMockRoot + "bitcoin/blockGraphtx/blk00000_tx-nocompressed.txt");

  auto start = high_resolution_clock::now();
  int blockReaded = 0;
  while(readBlock.is_open() && !readBlock.eof())
  {
    Block block;
    block.decode(readBlock);
    spyCBlockRPC::WrapperInformations wrapper;
    wrapper.setDelimitator("|");
    block.toTransactionsGraph(streamCppNotCompressed, wrapper);
    LOG(INFO) << "Block readed: " << blockReaded;
    blockReaded++;
  }
  auto end = high_resolution_clock::now();
  auto time = end - start;
  LOG(ERROR) << "\n\n -------- FINISH --------\n\n" <<"The time for serialized the block  uncompressed is: "
             << to_string((duration_cast<seconds>(time).count())) + " sec\n\n";
  streamCppNotCompressed.close();
}

TEST(serealization_compressed_test, serealization_util_test_compression_on_blk00000)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_util_test_compression_on_blk00000.log").c_str());

  ifstream readBlock(pathMockRoot + "/bitcoin/block/blk00000.dat");

  string pathCompressed = pathMockRoot + "bitcoin/blockGraphtx/blk00000_tx-compressed.dat";
  gzFile file = gzopen(pathCompressed.c_str(), "wb");
  auto start = high_resolution_clock::now();
  int blockReaded = 0;
  while(readBlock.is_open() && !readBlock.eof())
  {
    Block block;
    block.decode(readBlock);
    spyCBlockRPC::WrapperInformations wrapperTwo;
    wrapperTwo.setDelimitator("|");
    block.toCompressedTransactionsGraph(file, wrapperTwo);
    LOG(WARNING) << "Block readed: " << blockReaded;
    blockReaded++;
  }
  auto end = high_resolution_clock::now();
  auto time = end - start;
  LOG(ERROR) << "\n\n -------- FINISH --------\n\n" <<"The time for serialized the block compressed is: "
             << to_string((duration_cast<seconds>(time).count())) + " sec\n\n";
  gzclose(file);
}

TEST(serealization_compressed_test, serealization_util_test_no_compression_blk_on_blk00450)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_util_test_no_compression_blk_on_blk00450.log").c_str());

  ifstream readBlock(pathMockRoot + "/bitcoin/block/blk00450.dat");
  ofstream streamCppNotCompressed(pathMockRoot + "bitcoin/blockGraphtx/blk00450_tx-nocompressed.txt");

  auto start = high_resolution_clock::now();
  int blockReaded = 0;
  while(readBlock.is_open() && !readBlock.eof())
  {
    Block block;
    block.decode(readBlock);
    spyCBlockRPC::WrapperInformations wrapper;
    wrapper.setDelimitator("|");
    block.toTransactionsGraph(streamCppNotCompressed, wrapper);
    LOG(INFO) << "Block readed: " << blockReaded;
    blockReaded++;
  }
  auto end = high_resolution_clock::now();
  auto time = end - start;
  LOG(ERROR) << "\n\n -------- FINISH --------\n\n" <<"The time for serialized the block  uncompressed is: "
             << to_string((duration_cast<seconds>(time).count())) + " sec\n\n";
  streamCppNotCompressed.close();
}

TEST(serealization_compressed_test, serealization_util_test_compression_on_blk00450)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = true;
  google::SetLogDestination(google::ERROR, pathLogRoot.append("serealization_util_test_compression_on_blk00450.log").c_str());

  ifstream readBlock(pathMockRoot + "/bitcoin/block/blk00450.dat");

  string pathCompressed = pathMockRoot + "bitcoin/blockGraphtx/blk00450_tx-compressed.dat";
  gzFile file = gzopen(pathCompressed.c_str(), "wb");
  auto start = high_resolution_clock::now();
  int blockReaded = 0;
  while(readBlock.is_open() && !readBlock.eof())
  {
    Block block;
    block.decode(readBlock);
    spyCBlockRPC::WrapperInformations wrapperTwo;
    wrapperTwo.setDelimitator("|");
    block.toCompressedTransactionsGraph(file, wrapperTwo);
    LOG(WARNING) << "Block readed: " << blockReaded;
    blockReaded++;
  }
  auto end = high_resolution_clock::now();
  auto time = end - start;
  LOG(ERROR) << "\n\n -------- FINISH --------\n\n" <<"The time for serialized the block compressed is: "
             << to_string((duration_cast<seconds>(time).count())) + " sec\n\n";
  gzclose(file);
}


