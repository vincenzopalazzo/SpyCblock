//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <cmath>
#include <uv.h>

#include <glog/logging.h>
#include "../../util/serialize.h"

#include "DVarInt.h"

DVarInt::~DVarInt()
{}

uint64_t DVarInt::getValue() const
{
    return value;
}

void DVarInt::decode(std::ifstream &stream)
{
    value = ReadCompactSize(stream);
    LOG(INFO) << "Variant int read is: " << value;
}

