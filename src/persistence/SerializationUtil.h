// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SERIALIZATIONUTIL_H
#define SERIALIZATIONUTIL_H

#include <string>

#include "../structure/type/DVarInt.h"
#include "../util/serialize.h"
#include "../util/uint256.h"

using namespace std;

/**
 * The attual unit type using a Bitocin core is for the numerical type using
 * littele endian and for not numerical numbar using a big endian There are a
 * references
 * https://bitcoin.stackexchange.com/questions/22019/what-parts-of-bitcoin-litecoin-etc-are-little-endian
 * https://bitcoin.stackexchange.com/questions/2063/why-does-the-bitcoin-protocol-use-the-little-endian-notation
 * @author https://github.com/vincenzopalazzo
 */
namespace spyCBlock {

class SerializationUtil {
 private:
  SerializationUtil();

 public:
  static string toSerializeForm(uint8_t value8);

  static string toSerializeForm(int8_t value8);

  static string toSerializeForm(uint16_t value16);

  static string toSerializeForm(int16_t value16);

  static string toSerializeForm(uint32_t value32);

  static string toSerializeForm(int32_t value32);

  static string toSerializeForm(uint64_t value64);

  static string toSerializeForm(int64_t value64);

  static string toSerializeForm(DVarInt valueVarInt);

  static string toSerializeForm(uint256 value256);
};

}  // namespace spyCBlock

#endif  // SERIALIZATIONUTIL_H
