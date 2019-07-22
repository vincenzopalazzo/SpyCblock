#include <sstream>

#include <glog/logging.h>
#include "../../util/serialize.h"

#include "TransactionOutput.h"
#include "../../persistence/SerializationUtil.h"
#include "../../crypto/CryptoCore.h"

using namespace spyCBlock;
using namespace std;
using namespace nlohmann;

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */
void TransactionOutput::decode(ifstream &stream)
{
    Unserialize(stream, nValue);
    LOG(INFO) << "N value " << nValue;
    script.decode(stream);
    LOG(INFO) << "Script Lenght: " << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value: " << script.toString();

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

json TransactionOutput::toJson()
{
  json txOutputjson = json::object({
                                     {"ammount", this->nValue},
                                     {"scriptLenght", this->script.getScriptLenght().getValue()},
                                     {"script", this->getScript().getRawScriptString()},
                                     {"hashOutputTransaction", this->hashOutputTransaction},
                                   });

  return txOutputjson;
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
