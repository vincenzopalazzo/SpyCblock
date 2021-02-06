// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "DVarInt.h"

#include <glog/logging.h>

#include "../../util/serialize.h"

using namespace spyCBlock;

uint64_t DVarInt::getValue() const { return value; }

void DVarInt::decode(std::ifstream &stream) {
  value = ReadCompactSize(stream);
  LOG(INFO) << "Variant int read is: " << value;
}
