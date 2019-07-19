#ifndef SERIALIZATIONUTIL_H
#define SERIALIZATIONUTIL_H

#endif // SERIALIZATIONUTIL_H

#include <string>

#include "../util/serialize.h"
#include "../structure/type/DVarInt.h"
#include "../util/uint256.h"

using namespace std;

/**
 * The attual unit type using a Bitocin core is for the numerical type using littele endian
 * and for not numerical numbar using a big endian
 * There are a references
 * https://bitcoin.stackexchange.com/questions/22019/what-parts-of-bitcoin-litecoin-etc-are-little-endian
 * https://bitcoin.stackexchange.com/questions/2063/why-does-the-bitcoin-protocol-use-the-little-endian-notation
 * @author https://github.com/vincenzopalazzo
 */
//Trasforma questa classe in una classe statica, il patter singleton non
//e' una buona idea in questo caso
namespace spyCBlock
{

  class SerializationUtil
  {

    private:
      SerializationUtil();

    public:

      static string toSerealizeForm(uint8_t value8);


      static string toSerealizeForm(int8_t value8);


      static string toSerealizeForm(uint16_t value16);


      static string toSerealizeForm(int16_t value16);


      static string toSerealizeForm(uint32_t value32);


      static string toSerealizeForm(int32_t value32);


      static string toSerealizeForm(uint64_t value64);


      static string toSerealizeForm(int64_t value64);


      static string toSerealizeForm(DVarInt valueVarInt);


      static string toSerealizeForm(uint256 value256);


  };

}
