//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#include <sstream>
#include "TransactionOutput.h"
#include "../../util/serialize.h"
#include <glog/logging.h>
#include "../../persistence/serializationutil.h"

using namespace spyCBlock;

void TransactionOutput::decode(ifstream &stream) {
    Unserialize(stream, nValue);
    LOG(INFO) << "N value " << nValue;
    script.decode(stream);
    LOG(INFO) << "Script Lenght: " << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value: " << script.toString();
}

string TransactionOutput::toSerealizationForm()
{
  stringstream stream;
  stream << SerializationUtilSingleton::getInstance()->toSerealizeForm(this->nValue)
         << SerializationUtilSingleton::getInstance()->toSerealizeForm(this->getScript().getScriptLenght())
         << this->script.getScriptToSerializationForm();
  return stream.str();
}

json TransactionOutput::toJson()
{
  return json::object({
                        {"ammount", this->nValue},
                        {"scriptLenght", this->script.getScriptLenght().getValue()},
                        {"script", this->getScript().getRawScriptString()}
                      });
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
    stream << script.getScriptString() << endl;
    return stream.str();
}
