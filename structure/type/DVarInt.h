//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#ifndef PARSINGBLOCKCHAIN_CVARINT_H
#define PARSINGBLOCKCHAIN_CVARINT_H

#include <fstream>
#include "../../util/serialize.h"

class DVarInt{

private:
    uint64_t value;
    //CCompactSize newValue;

public:

    virtual ~DVarInt();

    uint64_t getValue() const;

    void decode(std::ifstream &stream);
};

#endif //PARSINGBLOCKCHAIN_CVARINT_H
