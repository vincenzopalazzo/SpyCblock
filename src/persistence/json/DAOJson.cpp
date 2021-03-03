// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "DAOJson.h"

#include <glog/logging.h>

#include <chrono>
#include <experimental/filesystem>

#include "../DAOException.h"

using namespace spyCBlock;
using namespace rapidjson;
using namespace std;
using namespace chrono;
namespace fs = std::experimental::filesystem;

bool DAOJson::saveBlock(const string& inputPath, const string& outputPath) {
  if (inputPath.empty() || outputPath.empty()) {
    LOG(WARNING) << "Error, the input arguments are empty";
    throw DAOException("Error, the input arguments are empty");
  }

  if (fs::exists(inputPath)) {
    if (!fs::is_directory(inputPath)) {
      ifstream loadFileDat(inputPath);
      ofstream saveBlkToJson(outputPath);
      if (!saveBlkToJson.is_open()) {
        LOG(ERROR) << "The file output not open " + outputPath;
        throw DAOException("The file output not open in tha path " +
                           outputPath);
      }
      OStreamWrapper streamWrapper(saveBlkToJson);
      Writer<OStreamWrapper> writer(streamWrapper);
      if (loadFileDat.is_open()) {
        writer.StartObject();
        writer.Key("blocks");
        writer.StartArray();
        Block block;
        chrono::milliseconds start = duration_cast<milliseconds>(
            chrono::system_clock::now().time_since_epoch());
        while (!loadFileDat.eof()) {
          block.decode(loadFileDat);
          block.toJson(writer);
        }
        chrono::milliseconds end = duration_cast<milliseconds>(
            chrono::system_clock::now().time_since_epoch());
        milliseconds duration = (end - start);
        LOG(ERROR) << "Block readed in " +
                          to_string(
                              (duration.count() * milliseconds::period::num /
                               milliseconds::period::den)) +
                          " second";
        writer.EndArray();
        writer.EndObject();
        saveBlkToJson.close();
        return true;
      }
      LOG(ERROR) << "The file " + inputPath + " not opened";
      throw DAOException("The file " + inputPath + " not opened");
    }
    LOG(ERROR) << "The file input is a directory" << inputPath;
    throw DAOException("The file input is a directory " + inputPath);
  }
  LOG(ERROR) << "The file input not exist" << inputPath;
  throw DAOException("The file input not exist " + inputPath);
}

bool DAOJson::saveBlockCompress(const string& inputPath,
                                const string& outputPath) {
  // Do nothing
  return false;
}
