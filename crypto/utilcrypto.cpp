#include "utilcrypto.h"
#include <glog/logging.h>
#include <algorithm>

char* spyCBlock::UtilCrypto::ToHexIntoByte(string &hexData)
{
  LOG(INFO) << "The array Hex is: " << hexData;

  vector<char*> *bytes = new vector<char*>();
  for(unsigned i = 0; i < hexData.length(); i += 2)
  {
      string byteSubString = hexData.substr(i, 2);
      char* byte = (char*)strtol(byteSubString.c_str(), NULL, 16);
      bytes->push_back(byte);

  }

  return ToVectorByteIntoArray(bytes);
}

vector<unsigned char> spyCBlock::UtilCrypto::ToHexIntoVectorByte(string &hexData)
{
  LOG(INFO) << "The array Hex is: " << hexData;

  vector<unsigned char> *bytes = new vector<unsigned char>();
  for(unsigned i = 0; i < hexData.length(); i += 2)
  {
      string byteSubString = hexData.substr(i, 2);
      unsigned char byte = (unsigned char)strtol(byteSubString.c_str(), NULL, 16);
      bytes->push_back(byte);

  }
  return *bytes;
}



char *spyCBlock::UtilCrypto::ToVectorByteIntoArray(vector<char *> *vectorByte)
{
  //TODO guardia

  //const int LENGHT = vectorByte->size();

  char* byte = *vectorByte->data();

  //https://stackoverflow.com/questions/37484796/converting-from-a-stdvectorint-to-a-char-c
  //transform(begin(*vectorByte), end(*vectorByte), begin(byte), [](int i) { return '0' + i; });
  return byte;
}
