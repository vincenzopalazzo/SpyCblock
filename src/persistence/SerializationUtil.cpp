// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "SerializationUtil.h"

#include <glog/logging.h>

#include "../util/endian.h"
#include "../util/strencodings.h"
#include "../util/uint256.h"

using namespace spyCBlock;

SerializationUtil::SerializationUtil() {}

string SerializationUtil::toSerializeForm(uint8_t value8) {
  string formLiteEndian;
  stringstream stream;
  stream.write((char *)&value8, 1);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerializeForm(int8_t value8) {
  string formLiteEndian;
  stringstream stream;
  stream.write((char *)&value8, 1);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtil::toSerializeForm(uint16_t value16) {
  string formLiteEndian;
  value16 = htole16(value16);
  stringstream stream;
  stream.write((char *)&value16, 2);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerializeForm(int16_t value16) {
  string formLiteEndian;
  value16 = htole16(value16);
  stringstream stream;
  stream.write((char *)&value16, 2);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtil::toSerializeForm(uint32_t value32) {
  string formLiteEndian;
  value32 = htole32(value32);
  stringstream stream;
  stream.write((char *)&value32, 4);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerializeForm(int32_t value32) {
  string formLiteEndian;
  value32 = htole32(value32);
  stringstream stream;
  stream.write((char *)&value32, 4);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtil::toSerializeForm(uint64_t value64) {
  string formLiteEndian;
  value64 = htole64(value64);
  stringstream stream;
  stream.write((char *)&value64, 8);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerializeForm(int64_t value64) {
  string formLiteEndian;
  value64 = htole64(value64);
  stringstream stream;
  stream.write((char *)&value64, 8);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion uint16 with endian tipe is: "
            << formLiteEndian;
  return formLiteEndian;
}

// Look the template void WriteCompactSize(Stream& os, uint64_t nSize)
// inside the serialize.h
string SerializationUtil::toSerializeForm(DVarInt valueVarInt) {
  string hexConvert;
  /*stringstream *stream = new stringstream();
  *stream << std::hex << valueVarInt.getValue();
  hexConvert = stream->str();*/
  hexConvert = HexStr(to_string(valueVarInt.getValue()));
  LOG(INFO) << "spyCBlock::SerializationUtil: "
            << "The form convertion varint with hexadecimal form is: "
            << hexConvert;
  // delete stream;

  unsigned int dimensioVarInt = GetSizeOfCompactSize(valueVarInt.getValue());
  LOG_IF(ERROR, dimensioVarInt < 0) << "Error in the readed dimension of "
                                       "compact size, the dimension eraded is: "
                                    << dimensioVarInt;
  if (dimensioVarInt <= sizeof(unsigned char)) {
    int8_t value8 = static_cast<int8_t>(valueVarInt.getValue());
    return SerializationUtil::toSerializeForm(value8);
  } else if (dimensioVarInt <= sizeof(unsigned char) + sizeof(unsigned short)) {
    int16_t value16 = static_cast<int16_t>(valueVarInt.getValue());
    int8_t tmp = static_cast<int8_t>(253);
    return SerializationUtil::toSerializeForm(tmp) +
           SerializationUtil::toSerializeForm(value16);
  } else if (dimensioVarInt <= sizeof(unsigned char) + sizeof(unsigned int)) {
    int32_t value32 = static_cast<int32_t>(valueVarInt.getValue());
    int8_t tmp = static_cast<int8_t>(254);
    return SerializationUtil::toSerializeForm(tmp) +
           SerializationUtil::toSerializeForm(value32);
  } else {
    int64_t value64 = static_cast<int64_t>(valueVarInt.getValue());
    int8_t tmp = static_cast<int8_t>(255);
    return SerializationUtil::toSerializeForm(tmp) +
           SerializationUtil::toSerializeForm(value64);
  }
  LOG_IF(ERROR, true) << "The dimension not corret, There is no suitable type";
  return nullptr;
}

string SerializationUtil::toSerializeForm(uint256 value256) {
  stringstream streamReversUint256;
  string reverString = value256.GetHex();
  reverse(reverString.begin(), reverString.end());
  for (int i = 0; i < reverString.size(); i += 2) {
    if ((i + 2) > reverString.size()) {
      continue;
    }
    string subStringRevers = reverString.substr(i, 2);
    reverse(subStringRevers.begin(), subStringRevers.end());
    streamReversUint256 << subStringRevers;
  }
  return streamReversUint256.str();
}
