#ifndef SERIALIZATIONUTIL_H
#define SERIALIZATIONUTIL_H

#endif // SERIALIZATIONUTIL_H

#include <string>

#include "../util/serialize.h"
#include "../structure/type/DVarInt.h"

using namespace std;

/**
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


  };

}
