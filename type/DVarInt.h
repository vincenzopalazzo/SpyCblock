//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#ifndef PARSINGBLOCKCHAIN_CVARINT_H
#define PARSINGBLOCKCHAIN_CVARINT_H

#include <fstream>

class DVarInt{

private:
    unsigned value;

public:
    unsigned int getValue() const;

    void decode(std::ifstream &stream);
};

#endif //PARSINGBLOCKCHAIN_CVARINT_H
