// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <glog/logging.h>

#include "../util/endian.h"
#include "../util/strencodings.h"
#include "../util/uint256.h"

#include "SerializationUtil.h"

using namespace spyCBlock;

SerializationUtil::SerializationUtil(){}

string SerializationUtil::toSerealizeForm(uint8_t value8)
{
  string formLiteEndian;
  stringstream stream;
  stream.write((char*) &value8, 1);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerealizeForm(int8_t value8)
{
  string formLiteEndian;
  stringstream stream;
  stream.write((char*) &value8, 1);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtil::toSerealizeForm(uint16_t value16)
{
  string formLiteEndian;
  value16 = htole16(value16);
  stringstream stream;
  stream.write((char*) &value16, 2);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerealizeForm(int16_t value16)
{
  string formLiteEndian;
  value16 = htole16(value16);
  stringstream stream;
  stream.write((char*) &value16, 2);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtil::toSerealizeForm(uint32_t value32)
{
  string formLiteEndian;
  value32 = htole32(value32);
  stringstream stream;
  stream.write((char*) &value32, 4);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerealizeForm(int32_t value32)
{
  string formLiteEndian;
  value32 = htole32(value32);
  stringstream stream;
  stream.write((char*) &value32, 4);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtil::toSerealizeForm(uint64_t value64)
{
  string formLiteEndian;
  value64 = htole64(value64);
  stringstream stream;
  stream.write((char*) &value64, 8);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerealizeForm(int64_t value64)
{
  string formLiteEndian;
  value64 = htole64(value64);
  stringstream stream;
  stream.write((char*) &value64, 8);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtil::toSerealizeForm(DVarInt valueVarInt)
{
  string hexConvert;
  stringstream *stream = new stringstream();
  *stream << std::hex << valueVarInt.getValue();
  hexConvert = stream->str();
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion varint with hexadecimal form is: " << hexConvert;
  delete stream;

  unsigned int dimensioVarInt = GetSizeOfCompactSize(valueVarInt.getValue());
  LOG_IF(ERROR, dimensioVarInt < 0) << "Error in the readed dimension of compact size, the dimension eraded is: " << dimensioVarInt;
  if( dimensioVarInt <= sizeof (unsigned char)){
    int8_t value8 = valueVarInt.getValue();
    return SerializationUtil::toSerealizeForm(value8);
  }else if (dimensioVarInt <= sizeof (unsigned short) + sizeof (unsigned char)) {
    int16_t value16 = valueVarInt.getValue();
    stringstream stream;
    stream << SerializationUtil::toSerealizeForm(253) << SerializationUtil::toSerealizeForm(value16);
    return stream.str();
  }else if (dimensioVarInt <= sizeof (unsigned int) + sizeof (unsigned char)) {
      int32_t value32 = valueVarInt.getValue();
      stringstream stream;
      stream << SerializationUtil::toSerealizeForm(254) << SerializationUtil::toSerealizeForm(value32);
      return stream.str();
  }else{
      int64_t value64 = valueVarInt.getValue();
      stringstream stream;
      stream << SerializationUtil::toSerealizeForm(255) << SerializationUtil::toSerealizeForm(value64);
      return stream.str();
  }
  LOG_IF(ERROR, true) << "The dimension not corret, There is no suitable type";
}

string SerializationUtil::toSerealizeForm(uint256 value256)
{
  stringstream streamReversUint256;
  string reverString = value256.GetHex();
  reverse(reverString.begin(), reverString.end());
  for(int i = 0; i < reverString.size(); i += 2){
      if((i + 2) > reverString.size()){
          continue;
      }
    string subStringRevers = reverString.substr(i, 2);
    reverse(subStringRevers.begin(), subStringRevers.end());
    streamReversUint256 << subStringRevers;
  }
  return streamReversUint256.str();
}
