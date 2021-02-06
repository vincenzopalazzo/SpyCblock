// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef RESULTBENCHMARK_H
#define RESULTBENCHMARK_H

#include <chrono>
#include <string>
#include <vector>

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

namespace spyCBlock {
class ResultBenchMark {
protected:
  std::string nameBenckmark;
  std::vector<std::chrono::minutes> results;

public:
  inline void setNameBenchmark(std::string &nameBenchmark) {
    this->nameBenckmark = nameBenchmark;
  }

  inline void addResult(std::chrono::minutes result) {
    results.emplace_back(result);
  }

  inline void clearResult() { results.clear(); }

  inline void toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writer) {
    writer.StartObject();

    writer.Key("name");
    writer.String(nameBenckmark.c_str());

    writer.Key("time");
    writer.StartArray();

    for (auto result : results) {
      writer.Int(result.count());
    }

    writer.EndArray();
    writer.EndObject();
  }
};
} // namespace spyCBlock

#endif // RESULTBENCHMARK_H
