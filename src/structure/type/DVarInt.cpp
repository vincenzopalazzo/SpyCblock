// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <cmath>

#include <glog/logging.h>
#include "../../util/serialize.h"

#include "DVarInt.h"

using namespace spyCBlock;

uint64_t DVarInt::getValue() const
{
    return value;
}

void DVarInt::decode(std::ifstream &stream)
{
    value = ReadCompactSize(stream);

    LOG(INFO) << "Variant int read is: " << value;
}

