//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include "TransactionInput.h"



const OutPoint &TransactionInput::getOutpoint() const {
    return outpoint;
}

void TransactionInput::setOutpoint(const OutPoint &outpoint) {
    TransactionInput::outpoint = outpoint;
}


void TransactionInput::decode(std::ifstream &stream)
{
    outpoint.Unserialize(stream);
    this->script.decode(stream);
    Unserialize(stream, this->sequences);
}

uint32_t TransactionInput::getSequences() const {
    return sequences;
}

const DScript &TransactionInput::getScript() const {
    return script;
}

