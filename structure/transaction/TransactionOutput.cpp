//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#include <sstream>

#include <glog/logging.h>
#include "../../util/serialize.h"

#include "TransactionOutput.h"
#include "../../persistence/serializationutil.h"
#include "../../crypto/cryptosingleton.h"

using namespace spyCBlock;

TransactionOutput::~TransactionOutput()
{}

const int64_t& TransactionOutput::getNValue() const
{
    return nValue;
}

const DScript &TransactionOutput::getScript() const
{
  return script;
}

const string &TransactionOutput::getHashOutputTransaction() const
{
  return this->hashOutputTransaction;
}

void TransactionOutput::decode(ifstream &stream)
{
    Unserialize(stream, nValue);
    LOG(INFO) << "N value " << nValue;
    script.decode(stream);
    LOG(INFO) << "Script Lenght: " << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value: " << script.toString();

}

string TransactionOutput::toSerealizationForm()
{
  string hexForm = SerializationUtilSingleton::getInstance()->toSerealizeForm(this->nValue);
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->getScript().getScriptLenght());
  hexForm += this->script.getScriptToSerializationForm();

  return hexForm;
}

json TransactionOutput::toJson()
{
  //Creating hash transaction
  string hexForm = toSerealizationForm();
  this->hashOutputTransaction = CryptoSingleton::getIstance()->getHash256(hexForm);

  return json::object({
                        {"ammount", this->nValue},
                        {"scriptLenght", this->script.getScriptLenght().getValue()},
                        {"script", this->getScript().getRawScriptString()},
                        {"hashOutputTransaction", this->hashOutputTransaction},
                      });
}

string TransactionOutput::toString()
{
    string stringForm =  "N Value: ";
    stringForm += to_string(nValue);
    stringForm += " satoshi";
    stringForm += "\n";
    stringForm += script.getScriptString();
    stringForm += "\n";
    return stringForm;
}
