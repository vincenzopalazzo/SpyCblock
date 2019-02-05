//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#include "TransactionOutput.h"

void TransactionOutput::decode(ifstream &stream) {
    Unserialize(stream, nValue);
    script.decode(stream);
}

int64_t TransactionOutput::getNValue() const {
    return nValue;
}

const DScript &TransactionOutput::getScript() const {
    return script;
}
