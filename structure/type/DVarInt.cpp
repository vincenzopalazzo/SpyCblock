//
// Created on  2/4/19.
// @author https://github.com/vincenzopalazzo
//
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

