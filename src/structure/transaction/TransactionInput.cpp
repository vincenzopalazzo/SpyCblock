// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <sstream>

#include <glog/logging.h>

#include "TransactionInput.h"
#include "../../persistence/SerializationUtil.h"
#include "../../crypto/CryptoCore.h"

using namespace spyCBlock;
using namespace std;

void TransactionInput::decode(std::ifstream &stream)
{
    outpoint.Unserialize(stream);
    LOG(WARNING) << "Outopoint Hash: " << outpoint.getHash().GetHex();
    LOG(WARNING) << "Outopoint N: " << outpoint.getN();
    this->script.decode(stream);
    LOG(INFO) << "Script Lenght" << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value" << script.toString();
    Unserialize(stream, this->sequences);
    LOG(INFO) << "Number sequences " << sequences;

    //Create hash transaction
    /*string hexInputTransaction = toSerealizationForm();
    this->hashInputTransaction = CryptoSingleton::getIstance().getHash256(hexInputTransaction);*/
}

string TransactionInput::toSerealizationForm() const
{
  string hexForm = SerializationUtil::toSerealizeForm(this->outpoint.getHash());
  hexForm.append(SerializationUtil::toSerealizeForm(this->outpoint.getN()));
  hexForm.append(SerializationUtil::toSerealizeForm(this->getScript().getScriptLenght()));
  hexForm.append(this->script.getScriptToSerializationForm());
  hexForm.append(SerializationUtil::toSerealizeForm(this->sequences));

  return hexForm;
}

bool TransactionInput::isScriptNull()
{
  LOG_IF(ERROR, script.getRawScriptString().empty()) << "The scrips is null";
  return this->script.getRawScriptString().empty();
}

void TransactionInput::toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson)
{
  writerJson.StartObject();

  /*writerJson.Key("hashInputTransaction");
  writerJson.String(this->hashInputTransaction.c_str());*/

  writerJson.Key("outputTxHash");
  writerJson.String(outpoint.getHash().ToString().c_str());

  writerJson.Key("aamount");
  writerJson.Uint(outpoint.getN());

  writerJson.Key("scriptLenght");
  writerJson.Uint64(this->getScript().getScriptLenght().getValue());

  writerJson.Key("script");
  writerJson.String(this->script.getRawScriptString().c_str());

  writerJson.Key("sequences");
  writerJson.Uint(this->sequences);

  writerJson.EndObject();
}

void TransactionInput::toGraphForm(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  wrapper.setHashPreviousTx(this->outpoint.getHash().GetHex());
  wrapper.setNOutpoint(this->outpoint.getN());
}

void TransactionInput::toTransactionsGraph(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  wrapper.setFrom(this->outpoint.getHash().GetHex());
}

string TransactionInput::toString()
{
    string stringForm = outpoint.ToString();
    stringForm += script.getScriptToSerializationForm();
    stringForm += "\n";
    stringForm += "Sequences: ";
    stringForm += to_string(sequences);
    stringForm += "\n";
    return stringForm;
}

//getter and setter
const OutPoint &TransactionInput::getOutpoint() const
{
    return outpoint;
}

void TransactionInput::setOutpoint(const OutPoint &outpoint)
{
  TransactionInput::outpoint = outpoint;
}

const string& TransactionInput::getHashInputTransaction() const
{
  return hashInputTransaction;
}

uint32_t TransactionInput::getSequences() const
{
    return sequences;
}

const DScript &TransactionInput::getScript() const
{
    return script;
}
