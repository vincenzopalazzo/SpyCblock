//@author https://github.com/vincenzopalazzo

#include <sstream>

#include <glog/logging.h>
#include "../../util/serialize.h"

#include "TransactionOutput.h"
#include "../../persistence/SerializationUtil.h"
#include "../../crypto/CryptoCore.h"

using namespace spyCBlock;
using namespace std;

void TransactionOutput::decode(ifstream &stream)
{
    Unserialize(stream, nValue);
    LOG(INFO) << "N value " << nValue;
    script.decode(stream);
    LOG(INFO) << "Script Lenght: " << script.getScriptLenght().getValue();
    LOG(WARNING) << "Script Value: " << script.toString();

    //Creating hash transaction
    string hexForm = toSerealizationForm();
    this->hashOutputTransaction = CryptoSingleton::getIstance().getHash256(hexForm);

}

string TransactionOutput::toSerealizationForm() const
{
  string hexForm = SerializationUtil::toSerealizeForm(this->nValue);
  hexForm += SerializationUtil::toSerealizeForm(this->getScript().getScriptLenght());
  hexForm += this->script.getScriptToSerializationForm();

  return hexForm;
}

void TransactionOutput::toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson)
{
   writerJson.StartObject();

   writerJson.Key("hashOutputTransaction");
   writerJson.String(this->hashOutputTransaction.c_str());

   writerJson.Key("ammount");
   writerJson.Int64(this->nValue);

   writerJson.Key("scriptLenght");
   writerJson.Uint64(this->script.getScriptLenght().getValue());

   writerJson.Key("script");
   writerJson.String(this->script.getRawScriptString().c_str());

   writerJson.EndObject();
}

void TransactionOutput::toGraphForm(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  wrapper.addInformationLink("Ammount: " + to_string(this->nValue));
  wrapper.setTo(this->getScript().getRawScriptString());
}

void TransactionOutput::toTransactionsGraph(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  //TODO add ammount to link graph
  wrapper.addInformationLink("Ammount: " + to_string(this->nValue));
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

//Subrutine

bool TransactionOutput::isScriptNull()
{
  return this->script.getRawScriptString().empty();
}

//getter and setter
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