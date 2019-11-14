// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <vector>
#include <experimental/filesystem>
#include <iostream>

#include <glog/logging.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../../include/cpp-properties/include/Properties.h"
#include "../../include/cpp-properties/include/PropertiesParser.h"
#include "../../src/core/SpyCBlock.h"
#include "../../src/persistence/graph/DAOManagerGraph.h"
#include "../../src/persistence/graph/transactions/DAOTransactionsGraph.h"
#include "../../src/persistence/json/DAOJson.h"
#include "../../src/core/ConfiguratorSingleton.h"

#include "ResultBenchMark.h"

void displayInformation();
void toJson(std::vector<spyCBlock::ResultBenchMark> &results);

int main()
{

  const int logLevel = spyCBlock::ConfiguratorSingleton::getInstance().getLevelLog();

  FLAGS_minloglevel = logLevel;
  FLAGS_logtostderr = false;
  google::InitGoogleLogging(std::to_string(logLevel).c_str());
  displayInformation();
   std::vector<spyCBlock::ResultBenchMark> result;
   std::vector<std::string> typeDeserializzation = {
                                            "uncompressed-tx",
                                            "compresse-tx",
                                            "json-uncompressed"
                                           };
   std::vector<int> directory = {10, 20, 30};
   int iterationrForBenchmark = 5;
   std::string root = std::experimental::filesystem::current_path();

   cppproperties::Properties prop = cppproperties::PropertiesParser::Read(root + "/conf.properties");

   string fromDir = prop.GetProperty("PATH_BLOCK_DAT") + "/";
   string toDir = prop.GetProperty("PATH_BLOCK_DECODE") + "/";

   int type = 0;
   while(size_t(type) < typeDeserializzation.size())
   {
       std::string typeAnlisis = typeDeserializzation.at(size_t(type));
       int onData = 0;
       while(size_t(onData) < directory.size())
       {
         int numFile = directory.at(size_t(onData));
         spyCBlock::SpyCBlock spyCBlock;
         spyCBlock.setHowFileWilBeRead(numFile);
         spyCBlock.resetFileToStartReadNum();
         cout << "Nex number file will be read: " << numFile << endl;
         int parallel = true; //TODO change this to false, this is setted to true because now I want data only for testing the paralel esecution
         spyCBlock::ResultBenchMark resultBenchmark;
         int i = 0;
         while(i < 5 || parallel == false)
         {
            spyCBlock.resetFileToStartReadNum();
            if(typeAnlisis == "uncompressed-tx"){
               spyCBlock.setCompressed(false);
               cout << "Uncompressed-tx\n";
               spyCBlock::DAOTransactionsGraph dao;
               std::string name = std::to_string(numFile) + "-"  + typeAnlisis + (parallel == false ? "" : "-parallel");
               resultBenchmark.setNameBenchmark(name);
               cout << "Iteration " << i + 1 << " for benchmark " << name << endl;
               if(parallel){
                   auto start = std::chrono::system_clock::now();
                   spyCBlock.convertDataParallel<spyCBlock::DAOTransactionsGraph>(dao, fromDir, toDir);
                   auto end = std::chrono::system_clock::now();
                   std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start);
                   resultBenchmark.addResult(minutes);
                   std::cout << "********** " << minutes.count() << " minutes\n";
               }else{
                  auto start = std::chrono::system_clock::now();
                  spyCBlock.convertData<spyCBlock::DAOTransactionsGraph>(dao, fromDir, toDir);
                  auto end = std::chrono::system_clock::now();
                  std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start);
                  resultBenchmark.addResult(minutes);
                  std::cout << "********** " << minutes.count() << " minutes\n";
               }
            }else if(typeAnlisis == "compresse-tx"){
               spyCBlock.setCompressed(true);
               cout << "Compressed-tx\n";
               spyCBlock::DAOTransactionsGraph dao;
               std::string name = std::to_string(numFile) + (parallel == false ? "" : "-parallel");
               resultBenchmark.setNameBenchmark(name);
               cout << "Iteration " << i + 1 << " for benchmark " << name << endl;
               if(parallel){
                   auto start = std::chrono::system_clock::now();
                   spyCBlock.convertDataParallel<spyCBlock::DAOTransactionsGraph>(dao, fromDir, toDir);
                   auto end = std::chrono::system_clock::now();
                   std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start);
                   resultBenchmark.addResult(minutes);
                   std::cout << "********** " << minutes.count() << " minutes\n";
               }else{
                  auto start = std::chrono::system_clock::now();
                  spyCBlock.convertData<spyCBlock::DAOTransactionsGraph>(dao, fromDir, toDir);
                  auto end = std::chrono::system_clock::now();
                  std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start);
                  resultBenchmark.addResult(minutes);
                  std::cout << "********** " << minutes.count() << " minutes\n";
               }
            }else{
                cout << "JSON-uncompressed\n";
                spyCBlock.setCompressed(false);
                spyCBlock::DAOJson dao;
                std::string name = std::to_string(numFile) + (parallel == false ? "" : "-parallel");
                resultBenchmark.setNameBenchmark(name);
                cout << "Iteration " << i + 1 << " for benchmark " << name << endl;
                if(parallel){
                    auto start = std::chrono::system_clock::now();
                    spyCBlock.convertDataParallel<spyCBlock::DAOJson>(dao, fromDir, toDir);
                    auto end = std::chrono::system_clock::now();
                    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start);
                    resultBenchmark.addResult(minutes);
                    std::cout << "********** " << minutes.count() << " minutes\n";
                }else{
                   auto start = std::chrono::system_clock::now();
                   spyCBlock.convertData<spyCBlock::DAOJson>(dao, fromDir, toDir);
                   auto end = std::chrono::system_clock::now();
                   std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start);
                   resultBenchmark.addResult(minutes);
                   std::cout << "********** " << minutes.count() << " minutes\n";
                }
            }
            i++;
            if(i >= 5 && parallel == false){
              parallel = true;
              i = 0;
              result.emplace_back(resultBenchmark);
              spyCBlock::ResultBenchMark resultBenchmarkTmp;
              resultBenchmark = resultBenchmarkTmp;
              cout << "Number benckmark: " << result.size() << endl;
            }

         }
         result.emplace_back(resultBenchmark);
         cout << "Number benckmark: " << result.size();
         toJson(result);
         onData++;
       }
       type++;
   }

}

void displayInformation(){
  cout << "\n\n\nCopyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com\n";
  cout << "Distributed under the Apache License Version 2.0 software license,\n";
  cout << "see https://www.apache.org/licenses/LICENSE-2.0.txt\n\n\n";
  cout << " *************** BENCHMARK SpyCBlock ***************\n";
}

void toJson(std::vector<spyCBlock::ResultBenchMark> &results){
  std::string pathOut = "result/json/scalability-benckmark-{YOUR-DETAILS-CPU-COMPILER}.json";
  std::ofstream saveBenckmark(pathOut);
  rapidjson::OStreamWrapper streamWrapper(saveBenckmark);
  rapidjson::Writer<rapidjson::OStreamWrapper> writer(streamWrapper);

  writer.StartObject();
  writer.Key("benchmarks");
  writer.StartArray();

  for(spyCBlock::ResultBenchMark result : results)
  {
    result.toJson(writer);
  }

  writer.EndArray();
  writer.EndObject();
  saveBenckmark.close();
}

