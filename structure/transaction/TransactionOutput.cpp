//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#include <sstream>
#include "TransactionOutput.h"
#include "../../util/serialize.h"
#include <glog/logging.h>

void TransactionOutput::decode(ifstream &stream) {
    Unserialize(stream, nValue);
    LOG(INFO) << "N value " << nValue;
    script.decode(stream);
    LOG(INFO) << "Script Lenght: " << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value: " << script.toString();
}

int64_t TransactionOutput::getNValue() const {
    return nValue;
}

const DScript &TransactionOutput::getScript() const {
    return script;
}

string TransactionOutput::toString() {
    stringstream stream;
    stream << "N Value: " << nValue << " satoshi" << endl;
    stream << script.toString();
    return stream.str();
}
