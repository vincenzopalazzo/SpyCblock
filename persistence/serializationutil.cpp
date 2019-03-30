/**
 * @author https://github.com/vincenzopalazzo
 */

#include "../persistence/serializationutil.h"
#include "../util/endian.h"
#include "glog/logging.h"
#include "../util/strencodings.h"

using namespace spyCBlock;

SerializationUtilSingleton* SerializationUtilSingleton::SINGLETON = nullptr; //Se levi questo causi errore sintattico ma perchè?

SerializationUtilSingleton::SerializationUtilSingleton()
{

}

SerializationUtilSingleton* SerializationUtilSingleton::getInstance()
{
  if(SerializationUtilSingleton::SINGLETON == nullptr)
  {
    SerializationUtilSingleton::SINGLETON = new SerializationUtilSingleton();
  }
  return SerializationUtilSingleton::SINGLETON;
}

string SerializationUtilSingleton::toSerealizeForm(uint8_t value8)
{
  string formLiteEndian;
  stringstream stream;
  stream.write((char*) &value8, 1);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtilSingleton::toSerealizeForm(int8_t value8)
{
  string formLiteEndian;
  stringstream stream;
  stream.write((char*) &value8, 1);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtilSingleton::toSerealizeForm(uint16_t value16)
{
  string formLiteEndian;
  value16 = htole16(value16);
  stringstream stream;
  stream.write((char*) &value16, 2);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtilSingleton::toSerealizeForm(int16_t value16)
{
  string formLiteEndian;
  value16 = htobe16(value16);
  stringstream stream;
  stream.write((char*) &value16, 2);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtilSingleton::toSerealizeForm(uint32_t value32)
{
  string formLiteEndian;
  value32 = htobe32(value32);
  stringstream stream;
  stream.write((char*) &value32, 4);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtilSingleton::toSerealizeForm(int32_t value32)
{
  string formLiteEndian;
  value32 = htobe32(value32);
  stringstream stream;
  stream.write((char*) &value32, 4);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string spyCBlock::SerializationUtilSingleton::toSerealizeForm(uint64_t value64)
{
  string formLiteEndian;
  value64 = htobe64(value64);
  stringstream stream;
  stream.write((char*) &value64, 8);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtilSingleton::toSerealizeForm(int64_t value64)
{
  string formLiteEndian;
  value64 = htobe64(value64);
  stringstream stream;
  stream.write((char*) &value64, 8);
  formLiteEndian = HexStr(stream.str());
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion uint16 with endian tipe is: " << formLiteEndian;
  return formLiteEndian;
}

string SerializationUtilSingleton::toSerealizeForm(DVarInt valueVarInt)
{
  string hexConvert;
  stringstream *stream = new stringstream();
  *stream << std::hex << valueVarInt.getValue();
  hexConvert = stream->str();
  LOG(INFO) << "spyCBlock::SerializationUtil: " << "The form convertion varint with hexadecimal form is: " << hexConvert;
  delete stream;
  return hexConvert;
}
