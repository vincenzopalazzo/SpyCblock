//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <sstream>
#include "TransactionInput.h"
#include <glog/logging.h>



const OutPoint &TransactionInput::getOutpoint() const {
    return outpoint;
}

void TransactionInput::setOutpoint(const OutPoint &outpoint) {
    TransactionInput::outpoint = outpoint;
}


void TransactionInput::decode(std::ifstream &stream)
{
    outpoint.Unserialize(stream);
    LOG(INFO) << "Outopoint Hash" << outpoint.getHash().GetHex();
    LOG(INFO) << "Outopoint N" << outpoint.getN();
    this->script.decode(stream);
    LOG(INFO) << "Script Lenght" << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value" << script.toString();
    Unserialize(stream, this->sequences);
    LOG(INFO) << "Numbar sequences " << sequences;
}

uint32_t TransactionInput::getSequences() const {
    return sequences;
}

const DScript &TransactionInput::getScript() const {
    return script;
}

string TransactionInput::toString() {
    stringstream stream;
    stream << outpoint.ToString();
    stream << script.toString();
    stream << "Sequences: " << sequences << endl;
    return stream.str();
}

