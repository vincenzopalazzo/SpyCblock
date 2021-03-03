#include <experimental/filesystem>

#include <benchmark/benchmark.h>
#include <glog/logging.h>

#include "../../src/core/ConfiguratorSingleton.h"
#include "../../src/core/SpyCBlock.h"
#include "../../src/persistence/graph/DAOManagerGraph.h"
#include "../../src/persistence/graph/transactions/DAOTransactionsGraph.h"
#include "../../src/persistence/json/DAOJson.h"

using namespace spyCBlock;
using namespace std;

string getRootPath() { return experimental::filesystem::current_path(); }

const string FILE_DIR = getRootPath() + "/file/";

void createGraphTxOneFile();
void createGraphIdWalletOneFile();
void decodeJsonOneFile();

// BM
void BM_createGraphTxOneFile(benchmark::State &state) {
  while (state.KeepRunning()) {
    createGraphTxOneFile();
  }
}

void BM_decodeJsonOneFile(benchmark::State &state) {
  while (state.KeepRunning()) {
    decodeJsonOneFile();
  }
}

void BM_decodeIDWalletOneFile(benchmark::State &state) {
  while (state.KeepRunning()) {
    createGraphIdWalletOneFile();
  }
}

BENCHMARK(BM_createGraphTxOneFile)->Arg(8);
BENCHMARK(BM_decodeJsonOneFile)->Arg(8);
// BENCHMARK(BM_decodeIDWalletOneFile)->Arg(8);

void createGraphTxOneFile() {
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  int logLevel = ConfiguratorSingleton::getInstance().getLevelLog();
  FLAGS_minloglevel = logLevel;
  FLAGS_logtostderr = false;
  google::InitGoogleLogging(std::to_string(logLevel).c_str());
  google::SetLogDestination(
      google::ERROR, pathLogRoot.append("unserialize_block_test.log").c_str());

  SpyCBlock spyCBlock;
  DAOTransactionsGraph dao;
  spyCBlock.convertData<DAOTransactionsGraph>(dao, FILE_DIR, FILE_DIR);
  benchmark::DoNotOptimize(pathLogRoot);
  // benchmark::DoNotOptimize(spyCBlock);
}

// for this I need configure bitcoind with mainet
void createGraphIdWalletOneFile() {
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  int logLevel = ConfiguratorSingleton::getInstance().getLevelLog();
  FLAGS_minloglevel = logLevel;
  FLAGS_logtostderr = false;
  google::InitGoogleLogging(std::to_string(logLevel).c_str());
  google::SetLogDestination(
      google::ERROR, pathLogRoot.append("unserialize_block_test.log").c_str());

  SpyCBlock spyCBlock;
  DAOManagerGraph dao;
  spyCBlock.convertData(dao, FILE_DIR, FILE_DIR);

  benchmark::DoNotOptimize(pathLogRoot);
  // benchmark::DoNotOptimize(spyCBlock);
}

void decodeJsonOneFile() {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
  int logLevel = ConfiguratorSingleton::getInstance().getLevelLog();
  FLAGS_minloglevel = logLevel;
  FLAGS_logtostderr = false;
  google::InitGoogleLogging(std::to_string(logLevel).c_str());
  google::SetLogDestination(
      google::ERROR, pathLogRoot.append("benchmark_single_file.log").c_str());

  SpyCBlock spyCBlock;
  DAOJson dao;
  spyCBlock.convertData(dao, FILE_DIR, FILE_DIR);
  benchmark::DoNotOptimize(pathLogRoot);
  // benchmark::DoNotOptimize(spyCBlock);
}

BENCHMARK_MAIN();
