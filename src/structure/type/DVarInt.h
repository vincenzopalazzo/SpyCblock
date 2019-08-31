#ifndef PARSINGBLOCKCHAIN_CVARINT_H
#define PARSINGBLOCKCHAIN_CVARINT_H

#include <fstream>

#include "../../util/serialize.h"

//@author https://github.com/vincenzopalazzo
namespace spyCBlock
{
  class DVarInt
  {
    public:

        uint64_t getValue() const;

        void decode(std::ifstream &stream);


    private:

      uint64_t value;
  };
}

#endif //PARSINGBLOCKCHAIN_CVARINT_H
