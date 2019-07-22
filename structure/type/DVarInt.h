#ifndef PARSINGBLOCKCHAIN_CVARINT_H
#define PARSINGBLOCKCHAIN_CVARINT_H

#include <fstream>

#include "../../util/serialize.h"

/**
 * Created on 2/4/19.
 * @author https://github.com/vincenzopalazzo
 */
namespace spyCBlock
{
  class DVarInt
  {
    private:
        uint64_t value;
        //CCompactSize newValue;

    public:

        uint64_t getValue() const;

        void decode(std::ifstream &stream);
  };
}

#endif //PARSINGBLOCKCHAIN_CVARINT_H
