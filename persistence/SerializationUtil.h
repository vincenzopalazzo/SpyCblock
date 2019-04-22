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

namespace spyCBlock
{

  class SerializationUtilSingleton
  {

  private:
    static spyCBlock::SerializationUtilSingleton* SINGLETON;
    //static constexpr string LOG = "spyCBlock::SerializationUtil: ";

  protected:
    SerializationUtilSingleton();

  public:

    static SerializationUtilSingleton* getInstance();


    string toSerealizeForm(uint8_t value8);


    string toSerealizeForm(int8_t value8);


    string toSerealizeForm(uint16_t value16);


    string toSerealizeForm(int16_t value16);


    string toSerealizeForm(uint32_t value32);


    string toSerealizeForm(int32_t value32);


    string toSerealizeForm(uint64_t value64);


    string toSerealizeForm(int64_t value64);


    string toSerealizeForm(DVarInt valueVarInt);


    string toSerealizeForm(uint256 value256);


  };

}
