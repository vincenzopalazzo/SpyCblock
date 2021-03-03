// Copyright (c) 2018-2021Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "TransactionOutput.h"

#include <glog/logging.h>

#include <sstream>

#include "../../crypto/CryptoCore.h"
#include "../../persistence/SerializationUtil.h"
#include "../../util/serialize.h"

using namespace spyCBlock;
using namespace std;

void TransactionOutput::decode(ifstream& stream) {
  Unserialize(stream, nValue);
  LOG(INFO) << "N value " << nValue;
  script.decode(stream);
  LOG(INFO) << "Script Lenght: " << script.getScriptLength().getValue();
  LOG(WARNING) << "Script Value: " << script.toString();

  // Creating hash transaction
  /*  string hexForm = toSerealizationForm();
    this->hashOutputTransaction =
    CryptoSingleton::getInstance().getHash256(hexForm);*/
}

string TransactionOutput::toSerealizationForm() const {
  string hexForm = SerializationUtil::toSerializeForm(this->nValue);
  hexForm +=
      SerializationUtil::toSerializeForm(this->getScript().getScriptLength());
  hexForm += this->script.getScriptToSerializationForm();

  return hexForm;
}

void TransactionOutput::toJson(
    rapidjson::Writer<rapidjson::OStreamWrapper>& writerJson) {
  writerJson.StartObject();

  /*writerJson.Key("hashOutputTransaction");
  writerJson.String(this->hashOutputTransaction.c_str());*/

  writerJson.Key("amount");
  writerJson.Int64(this->nValue);

  writerJson.Key("scriptLength");
  writerJson.Uint64(this->script.getScriptLength().getValue());

  writerJson.Key("script");
  writerJson.String(this->script.getRawScriptString().c_str());

  writerJson.EndObject();
}

void TransactionOutput::toGraphForm(
    ofstream& outputStream, spyCBlockRPC::WrapperInformations& wrapper) {
  wrapper.addInformationLink(
      spyCBlockRPC::WrapperInformations::TypeInsert::TRANSACTION,
      "amount: " + to_string(this->nValue));
  wrapper.setTo(this->getScript().getRawScriptString());
}

void TransactionOutput::toTransactionsGraph(
    ofstream& outputStream, spyCBlockRPC::WrapperInformations& wrapper) {
  wrapper.addInformationLink(
      spyCBlockRPC::WrapperInformations::TypeInsert::TRANSACTION,
      "amount: " +
          to_string(this->nValue));  // Not is the ammount of transaction
}

string TransactionOutput::toString() {
  string stringForm = "N Value: ";
  stringForm += to_string(nValue);
  stringForm += " satoshi";
  stringForm += "\n";
  stringForm += script.getScriptString();
  stringForm += "\n";
  return stringForm;
}

bool TransactionOutput::isScriptNull() {  // This isn't null but containt the
                                          // OP_RETURN, before introduce it,
                                          // some transaction are null.
  return this->script.getRawScriptString().empty();
}

// getter and setter
const int64_t& TransactionOutput::getNValue() const { return nValue; }

const DScript& TransactionOutput::getScript() const { return script; }

const string& TransactionOutput::getHashOutputTransaction() const {
  return this->hashOutputTransaction;
}
